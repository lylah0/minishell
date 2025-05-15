/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:36:38 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/15 22:06:39 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	wait_all(void)
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
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
	int	in_pipe;

	in_pipe = (prev_pipe != 0 || has_next_cmd(current));
	if (prev_pipe != 0 && !data->stdin_redir)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (has_redirection(current))
	{
		validate_redirections(current);
		redir(current, data);
	}
	if (has_next_cmd(current) && !data->stdout_redir)
		dup2(fd[1], STDOUT_FILENO);
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (prev_pipe != 0)
		close(prev_pipe);
	exec(current, data, env_path, in_pipe);
}

void	parent(int *prev_pipe, t_input **current, int fd[2])
{
	(void)data;
	if (*prev_pipe != 0)
		close(*prev_pipe);
	if (has_next_cmd(*current))
	{
		close(fd[1]);
		*prev_pipe = fd[0];
	}
	else if (fd[0] != -1)
		close(fd[0]);
	*current = get_next_command(*current);
}

void	exec_pipe(t_input *head, char *env_path, t_data *data)
{
	int		fd[2];
	int		prev_pipe;
	t_input	*current;

	prev_pipe = 0;
	current = head;
	while (current)
	{
		data->stdin_redir = 0;
		data->stdout_redir = 0;
		if (has_next_cmd(current))
			pipe(fd);
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		if (handle_parent_builtin(current, data))
		{
			current = get_next_command(current);
			continue ;
		}
		handle_fork(&prev_pipe, &current, fd, data, env_path);
	}
	wait_all();
}

