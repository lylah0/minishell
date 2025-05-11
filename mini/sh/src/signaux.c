/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:36:08 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/11 13:29:20 by monoguei         ###   ########.fr       */
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
	signal(SIGPIPE, SIG_IGN);
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

/*
| signal      | Définit un gestionnaire de signal      | `void (*)(int)` | Gérer des interruptions               | `SIG_ERR` si échec | `<signal.h>` |
| sigaction   | Modifie l'action associée à un signal  | `int`           | Pour des gestions de signaux avancées | -1 si erreur       | `<signal.h>` |
| sigemptyset | Initialise un ensemble de signaux vide | `int`           | Pour définir un masque de signaux     | -1 si erreur       | `<signal.h>` |
| sigaddset   | Ajoute un signal à un ensemble         | `int`           | Compléter le masque de signaux        | -1 si erreur       | `<signal.h>` |
| tcsetattr   | Modifie les attributs du terminal      | `int`           | Pour configurer le terminal                    | -1 si erreur          | `<termios.h>`                 |
| tcgetattr   | Récupère les attributs du terminal     | `int`           | Pour lire la config actuelle du terminal       | -1 si erreur          | `<termios.h>`                 |
|
 le code que retourne bash dans le cas d'un signal est 128 + le numéro du signal.

*/

