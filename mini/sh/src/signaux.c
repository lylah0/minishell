/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 07:36:08 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/12 16:55:37 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <termios.h>
#include <asm-generic/termbits.h>
#include <asm-generic/siginfo.h>
#include <asm/signal.h>

struct termios g_term_backup;
struct sigaction {
    void     (*sa_handler) (int);
    void     (*sa_sigaction) (int, siginfo_t *, void *);
    sigset_t   sa_mask;
    int        sa_flags;
    void     (*sa_restorer) (void);
};

//SIGINT signal interrupt ctrl + c interrompt/termine le processus courant.
__sighandler_t	handler_sigint(void)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	return (SIG_IGN);
}


void	handler_sigint2(int sig)
{
	ft_putstr_fd("\n", 1); // Affiche un retour à la ligne
	rl_replace_line("", 0); // Efface la ligne actuelle dans le prompt
	rl_on_new_line(); // Prépare une nouvelle ligne pour l'affichage
	rl_redisplay(); // Réaffiche le prompt
	sig++;
	return;
}

void	init_signals(void)
{
	struct termios term;
	
	signal(SIGPIPE, SIG_IGN);//(13, 1)
	signal(SIGQUIT, SIG_IGN);//ctrl+\ core dump quit proc chil en cours
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = ft_sigquit_handler;
	sigaction(SIGQUIT, &sa, NULL);
	signal(SIGINT, handler_sigint2);
	if (tcgetattr(0, &g_term_backup) == 0)
	{
		term = g_term_backup;
		term.c_lflag &= ~ECHOE;// pour ignorer lecho genre ^/
		term.c_lflag &= ~ECHOCTL; // pour ignorer l'affichage de ^\ pour SIGQUIT
		tcsetattr(0, 0, &term);// mod attribut term
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
				
 					au prompt			en cours dexcution
 
 ctrl + C	  ignore, efface ligne
 
 ctrl + \
 
 ctrl + D

// Gestionnaire de signal pour SIGINT (Ctrl + C)
static void	ft_sigint_handler(int num)
{
	(void)num; // Évite un avertissement pour le paramètre non utilisé

	// Si un processus enfant est en cours d'exécution
	if (g_minishell.signint_child)
	{
		ft_putstr_fd("\n", 1); // Affiche un retour à la ligne
		g_minishell.signint_child = false; // Réinitialise l'indicateur de signal pour le processus enfant
		g_minishell.heredoc_sigint = true; // Indique qu'un SIGINT a été reçu pendant un heredoc
	}
	else
	{
		ft_putstr_fd("\n", 1); // Affiche un retour à la ligne
		rl_replace_line("", 0); // Efface la ligne actuelle dans le prompt
		rl_on_new_line(); // Prépare une nouvelle ligne pour l'affichage
		rl_redisplay(); // Réaffiche le prompt
	}
}

void	ft_sigquit_handler(int num)
{
	(void)num;
	ft_putstr_fd("Quit: 3\n", 1);
}

void	ft_init_signals(void)
{
	struct termios	term;

	term = g_minishell.original_term;
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	g_minishell.heredoc_sigint = false;
	g_minishell.signint_child = false;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

[ ] implementer fonction sleep pour tester les signaux pour interrompre le process
[ ] comprendre le fonctionnement des signaux dans les childs
[ ] comprendre lutilisation des differentes fonctions impliquees
*/