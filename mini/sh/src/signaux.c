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

/// @brief EOF (Ctrl+D)
/// At the prompt: if the input is empty, exits the shell gracefully with cleanup.
/// Mimics the shell behavior to exit on end-of-input when no text is typed.
/// This is triggered when readline returns NULL.
char *get_user_input(const char *prompt)
{
	char *line;

	line = readline(prompt);
	if (!line)
	{
		fprintf(stderr, "Error reading line\n");
		return (NULL);
	}
	return (line);
}

static struct termios g_termios_backup;

/// @brief Stores or retrieves a persistent pointer to the global data structure.
/// @param new_data If not NULL, this value is stored for later retrieval.
/// @return The last stored pointer to t_data, or NULL if none was set.
t_data *get_data_ptr(t_data *new_data)
{
	static t_data *saved = NULL;
	if (new_data)
		saved = new_data;
	return (saved);
}

/// @brief SIGINT (Ctrl+C) : Used to cancel the current command input or interrupt a running process.
/// At the prompt: clears current line and re-displays the prompt.
/// During child execution: sends SIGINT to the child process to interrupt it.
void handler_sigint(int signum)
{
	t_data *data = get_data_ptr(NULL);
	(void)signum;

	if (data && data->signal)
		data->signal->sigint = ON;

	if (data && data->child_pid > 0)
		kill(data->child_pid, SIGINT);

	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/// @brief SIGQUIT (Ctrl+\)
/// At the prompt: ignored completely (no `Quit: 3`, no visual `^\\`).
/// During child execution: forwarded to the child process which may terminate and produce `Quit (core dumped)` if not handled.
/// Mimics bash behavior by hiding signal effect from the user at the prompt.
void handler_sigquit(int signum)
{
	t_data *data = get_data_ptr(NULL);
	(void)signum;
	
	if (data && data->signal)
		data->signal->sigint = ON;

	if (data && data->child_pid > 0)
	{
		kill(data->child_pid, SIGQUIT);
		
		ft_printf_stderr("Quit (core dumped)\n");
		// restore_terminal();
		exit_code = 131;
		exit(exit_code);
	}
	else
		return ;
}

/// @brief Sets up signal handlers and disables echoing of control characters like ^C and ^\.
/// @param data Pointer to the global minishell state structure.
void init_signals(t_data *data)
{
	struct termios term;

	get_data_ptr(data);
	// signal(SIGINT, handler_sigint);
	signal(SIGQUIT, handler_sigquit);

	tcgetattr(STDIN_FILENO, &term);
	g_termios_backup = term;

	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/// @brief Restores the original terminal attributes saved during initialization.
void restore_terminal(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_termios_backup);
}


