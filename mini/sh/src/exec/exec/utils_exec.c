/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:12:43 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/15 22:48:36 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_parent_builtin(char *token)
{
	if (!ft_strncmp(token, "cd", 3) || !ft_strncmp(token, "export", 7)
		|| !ft_strncmp(token, "unset", 6) || !ft_strncmp(token, "exit", 5))
		return (1);
	return (0);
}

int	handle_parent_builtin(t_input *current, t_data *data)
{
	if (is_builtin(current->token) && is_parent_builtin(current->token)
		&& !data->stdin_redir && !has_next_cmd(current))
	{
		kind_of_token(data, current, 0);
		return (1);
	}
	return (0);
}

void	handle_fork(int *prev_pipe, t_input **current, int *fd, t_data *data, char *env_path)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		data->child_pid = 0;// pour l'enfant, ne rien faire
		child(*prev_pipe, *current, fd, env_path, data);// ici cest une enfant
	}
	else
	{
		data->child_pid = pid;// memorisation du processus enfant pour que sigint puisse cibler le child
		parent(prev_pipe, current, fd);
	}
}

void	fill_cmd_args(char **cmd, t_input *token)
{
	int		i;
	t_input	*tmp;

	i = 1;
	tmp = token->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type != T_OP && tmp->type != T_PIPE
			&& (tmp->prev == NULL || tmp->prev->type != T_OP))
		{
			cmd[i] = ft_strdup(tmp->token);
			i++;
		}
		tmp = tmp->next;
	}
	cmd[i] = NULL;
}

int	count_args(t_input *token)
{
	int		count;
	t_input	*tmp;

	count = 1;
	tmp = token->next;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type != T_OP && tmp->type != T_PIPE
			&& (tmp->prev == NULL || tmp->prev->type != T_OP))
			count++;
		tmp = tmp->next;
	}
	return (count);
}
