/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:36:38 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/25 17:10:24 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	wait_all(void)
{
	int	status;

	while (wait(&status) > 0)
		;
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

t_input	*get_next_command(t_input *node)
{
	while (node && node->type != T_PIPE)
		node = node->next;
	if (node && node->type == T_PIPE)
		return (node->next);
	return (NULL);
}

void	child(int prev_pipe, t_input *current, int fd[2], char *env_path, t_data *data)
{
	if (prev_pipe != 0)
	{
		dup2(prev_pipe, 0);
		close(prev_pipe);
	}
	if (has_next_cmd(current))
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
	}
	if ((current->next && current->next->next) && (current->next->type == T_OP || current->next->next->type == T_OP))
		redir(current);
	exec(current, data, env_path);
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
		if (is_builtin(current->token) && is_parent_builtin(current->token) && prev_pipe == 0)
		{
			kind_of_token(data, current);
			current = get_next_command(current);
			continue;
		}
		pid = fork();
		if (pid == 0)
			child(prev_pipe, current, fd, env_path, data);
		else
			parent(&prev_pipe, &current, fd, &data);
	}
	wait_all();
}
