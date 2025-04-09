/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:36:08 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/09 15:39:32 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <termios.h>

struct termios g_term_backup;

//SIGINT signal interrupt ctrl + c interrompt/termine le processus courant.
__sighandler_t	handler_sigint(void)
{
//	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	// rl_redisplay();
	// maj exit_status
	return (SIG_IGN);
}

void	init_signals(void)
{
	struct termios term;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler_sigint());
	if (tcgetattr(0, &g_term_backup) == 0)
	{
		term = g_term_backup;
		term.c_lflag &= ~ECHOE;
		tcsetattr(0, 0, &term);
	}
}

void	restore_terminal(void)
{
	tcsetattr(0, 0, &g_term_backup);
}

