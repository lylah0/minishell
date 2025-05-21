// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   signaux.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/03 07:36:08 by monoguei          #+#    #+#             */
// /*   Updated: 2025/05/13 10:34:04 by monoguei         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"

static struct termios g_termios_backup;

char *get_user_input(t_data *data, const char *prompt)
{
	char *line;

	line = readline(prompt);
	if (!line)
	{
		restore_terminal();
		data->should_exit = YES;
		return (NULL);
	}
	return (line);
}

t_data *get_data_ptr(t_data *new_data)
{
	static t_data *saved = NULL;
	if (new_data)
		saved = new_data;
	return (saved);
}

void handler_sigint(int signum)
{
	t_data *data;
	(void)signum;

	data = get_data_ptr(NULL);
	if (data && data->signal)
		data->signal->sigint = ON;
	if (data && data->child_pid > 0)
		kill(data->child_pid, SIGINT);
	else
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void handler_sigquit(int signum)
{
	t_data *data;
	(void)signum;

	data = get_data_ptr(NULL);
	if (data && data->signal)
		data->signal->sigint = ON;
	if (data && data->child_pid <= 0)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		restore_terminal();
		kill(data->child_pid, SIGQUIT);
		ft_printf_stderr("Quit (core dumped)\n");
		exit(131);
	}
	return ;
}

// « La présence ou absence de l'écho de caractères de contrôle comme ^C ou
// ^\ dépend uniquement du réglage visuel du terminal (flag ECHOCTL dans la
// structure termios), et non du traitement réel des signaux. Ainsi, ne pas
// les afficher ne modifie aucunement le comportement fonctionnel imposé par
// le sujet et respecté par notre implémentation. »
void init_signals(t_data *data)
{
	struct termios term;

	get_data_ptr(data);
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
	tcgetattr(STDIN_FILENO, &term);
	g_termios_backup = term;
	// term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void restore_terminal(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_termios_backup);
}
