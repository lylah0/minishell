/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:14:21 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 16:20:42 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static struct termios	g_termios_backup;

char	*get_user_input(t_data *data, const char *prompt)
{
	char	*line;

	line = readline(prompt);
	if (!line)
	{
		restore_terminal();
		data->should_exit = YES;
		return (NULL);
	}
	return (line);
}

t_data	*get_data_ptr(t_data *new_data)
{
	static t_data	*saved = NULL;

	if (new_data)
		saved = new_data;
	return (saved);
}

void	handler_sigint(int signum)
{
	t_data	*data;

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

void	handler_sigquit(int signum)
{
	t_data	*data;

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

void	init_signals(t_data *data)
{
	struct termios	term;

	get_data_ptr(data);
	signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);
	tcgetattr(STDIN_FILENO, &term);
	g_termios_backup = term;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	restore_terminal(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_termios_backup);
}
