# minishell_ly_mo
// Enumération des différents types de tokens
typedef enum s_token_type
{
	T_CMD,          // Commande
	T_CMD_ARG,      // Argument de commande
	T_ARG,          // Argument générique
	T_FILE,         // Fichier (pour redirections)
	T_OP,           // Opérateur (<, >, etc.)
	T_PIPE,         // Pipe (|)
	T_SKIP,         // Token à ignorer
	T_WORD          // Mot générique
}					t_token_type;

// Structure représentant un token dans la liste chaînée
typedef struct s_input
{
	char			*token;         // Contenu du token
	t_token_type	type;           // Type du token
	struct s_input	*next;          // Pointeur vers le prochain token
	struct s_input	*prev;          // Pointeur vers le token précédent
	struct s_data	*data;          // Référence à la structure principale
}					t_input;

// Structure représentant une variable d'environnement
typedef struct s_env
{
	char 			*name;          // Nom de la variable
	char			*value;         // Valeur de la variable
	struct s_env 	*next;          // Pointeur vers la prochaine variable
}					t_env;

// Enumération des états des signaux
typedef enum e_signal_state
{
	SIGNAL_OFF,     // Signal désactivé
	SIGNAL_ON       // Signal activé
}					t_signal_state;

// Structure pour gérer les signaux
typedef struct s_signal
{
	t_signal_state	sigint;         // État du signal SIGINT
	t_signal_state	sigquit;        // État du signal SIGQUIT
}					t_signal;

// Structure principale contenant toutes les données du programme
typedef struct s_data
{
	t_input			*input;         // Liste chaînée des tokens
	t_env			*env;           // Liste chaînée des variables d'env
	t_signal		*signal;        // Gestion des signaux
	char			**copy_env;     // Copie de l'environnement format array
	char			*env_path;      // Chemin de l'environnement
	char			**array;        // Tableau temporaire pour les commandes
	int				should_exit;    // Indicateur pour quitter le programme
	int				exit_code;      // Code de sortie du programme
	int				stdout_redir;   // Descripteur pour la redirection de stdout
	int				stdin_redir;    // Descripteur pour la redirection de stdin
	pid_t			child_pid;      // PID du processus enfant
	int				pipe_op;        // Indicateur pour les opérations de pipe
}					t_data;
