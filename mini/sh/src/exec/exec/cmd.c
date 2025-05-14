/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:36:38 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/13 12:49:35 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// void wait_all(void)
// {
// 	int status;
// 	pid_t pid;

// 	while ((pid = wait(&status)) > 0)
// 	{
// 		if (WIFEXITED(status))
// 			exit_code = WEXITSTATUS(status);
// 	}
// }

// version gpt
void wait_all(void)
{
	int status;
	pid_t pid;

	while ((pid = wait(&status)) > 0)
	{
		if (WIFSIGNALED(status))
		{
			int sig = WTERMSIG(status);
			if (sig == SIGINT)
			{
				exit_code = 130; // bash: code pour interruption Ctrl+C
				write(1, "\n", 1); // propre
			}
		}
		else if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
	}
}


int	has_next_cmd(t_input *node)
{
	while (node)
	{
		if (node->type == T_PIPE)
			return (1);
		node = node->next;
	}
	return (0);
}

/// @brief 
/// @param node 
/// @return 
t_input	*get_next_command(t_input *node)
{
	while (node && node->type != T_PIPE)
		node = node->next;
	if (node && node->type == T_PIPE)
		return (node->next);
	return (NULL);
}

/// @brief Fonction qui exécute une commande dans un processus enfant.
/// @param prev_pipe Descripteur de fichier du pipe précédent (entrée).
/// @param current Pointeur vers le nœud actuel de la liste chaînée des commandes.
/// @param fd Tableau contenant les descripteurs de fichier pour le pipe actuel.
/// @param env_path Chemin vers les variables d'environnement.
/// @param data Structure contenant les données globales du programme.
void	child(int prev_pipe, t_input *current, int fd[2], char *env_path, t_data *data)
{
	if (prev_pipe != 0 && !data->stdin_redir)
	{
		dup2(prev_pipe, 0);
		close(prev_pipe);
	}
	if (has_next_cmd(current) && !data->stdout_redir)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	if (has_redirection(current))
	{
		validate_redirections(current);
		redir(current, data);
	}
	// Erreur : → execve() remplace le process courant. 
	// Si tu l'appelles dans une boucle, il ne revient jamais,
	//  mais si jamais exec() échoue, tu entres dans une boucle infinie.
	// while (data->signal->sigquit == OFF)
	// 	exec(current, data, env_path);
/*
execve() remplace entièrement le process enfant.
Donc :

Si exec() réussit → le process devient le programme externe

Si exec() échoue → tu passes à perror() et exit(1)

✅ Pas besoin de boucle
*/
	exec(current, data, env_path);

	// Si exec échoue :
	perror("minishell: exec failed");
	exit(1);
}

void	parent(int *prev_pipe, t_input **current, int fd[2], t_data **data)
{
	(void)data;
	if (*prev_pipe != 0)
		close(*prev_pipe);
	if (has_next_cmd(*current))
	{
		close(fd[1]);
		*prev_pipe = fd[0];
	}
	else if (fd[0])
		close(fd[0]);
	*current = get_next_command(*current);
}

/// @brief Fonction principale pour exécuter une série de commandes connectées par des pipes.
/// @param head Pointeur vers le premier nœud de la liste chaînée des commandes.
/// @param env_path Chemin vers les variables d'environnement.
/// @param data Structure contenant les données globales du programme.
void	exec_pipe(t_input *head, char *env_path, t_data *data)
{
	int		fd[2];
	int		prev_pipe;
	pid_t	pid;
	t_input	*current;

	prev_pipe = 0;
	current = head;
	fd[0] = 0;
	fd[1] = 0;
	while (current)
	{
		if (has_next_cmd(current))
			pipe(fd);
		if (is_builtin(current->token) && is_parent_builtin(current->token) && is_safe_to_exec_in_parent(current))
		{
			kind_of_token(data, current);
			current = get_next_command(current);
			continue;
		}
		pid = fork();
		if (pid == 0)
		{
			data->child_pid = 0;// pour l'enfant, ne rien faire
			child(prev_pipe, current, fd, env_path, data);// ici cest une enfant
		}
		else
		{
			data->child_pid = pid;// memorisation du processus enfant pour que sigint puisse cibler le child
			parent(&prev_pipe, &current, fd, &data);
		}
	}
	wait_all();
	data->child_pid = -1;// 💡 Ça évite de renvoyer un signal à un ancien pid non valide plus tard.
}
