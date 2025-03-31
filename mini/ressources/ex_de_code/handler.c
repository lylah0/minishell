#include <stdio.h>      // printf
#include <stdlib.h>     // free, exit
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>     // signal, SIGINT, SIGQUIT, SIG_IGN
#include <termios.h>    // termios, tcgetattr, tcsetattr
#include <unistd.h>     // STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO, write
#include <sys/wait.h>   // waitpid, WIFSIGNALED, WTERMSIG

struct termios g_term_backup;  // Sauvegarde de l'état initial du terminal

// Handler pour SIGINT (Ctrl+C)
void	handle_sigint(void)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	// Optionnel: mettre à jour un statut global pour $? à 130
}

// Initialisation des handlers de signaux pour le shell parent
void    init_signals(void)
{
	struct termios term;

	// Ignorer Ctrl-\ (SIGQUIT) pour ne pas quitter le shell
	signal(SIGQUIT, SIG_IGN);
	// Intercepter Ctrl-C (SIGINT) avec notre handler
	signal(SIGINT, handle_sigint);

	// Sauvegarder l'état initial du terminal
	if (tcgetattr(STDIN_FILENO, &g_term_backup) == 0)
	{
		term = g_term_backup;
		term.c_lflag &= ~ECHOCTL;  // Désactiver l'affichage de ctrl + /
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}

// Restaurer l'état du terminal après exécution d'une commande
void restore_terminal(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_term_backup);
}

int main(void)
{
	char *input;
	int  exit_status = 0;

	init_signals();
	while (1)
	{
		input = readline("minishell> ");
		if (!input) {                   // Ctrl+D (EOF) détecté
			write(STDOUT_FILENO, "exit\n", 5);
			break;                      // sortir de la boucle -> fin du shell
		}
		if (*input != '\0')
			add_history(input);

		// Avant d'exécuter une commande externe, restaurer le terminal
		restore_terminal();

		// Ici, on exécuterait la commande (parsing + execution)
		// ... (code d'exécution non montré)

		free(input);

		// Réinitialiser les signaux après l'exécution d'une commande
		init_signals();
	}
	return exit_status;
}
