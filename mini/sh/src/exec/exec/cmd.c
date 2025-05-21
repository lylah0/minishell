/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:36:38 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 09:06:31 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	wait_all(t_data *data)
{
	int		status;
	pid_t	pid;

	while ((pid = wait(&status)) > 0)
	{
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
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

void	child(t_data *data, int prev_pipe, t_input *current, int fd[2],
		char *env_path)
{
	int	in_pipe;

	data->stdin_redir = 0;
	data->stdout_redir = 0;
	in_pipe = (prev_pipe != 0 || has_next_cmd(current));
	if (prev_pipe != 0 && !data->stdin_redir)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (has_redirection(current))
	{
		validate_redirections(data, current);
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
	exec(data, current, env_path, in_pipe);
}

void	parent(int *prev_pipe, t_input **current, int fd[2])
{
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

void	exec_pipe(t_data *data, t_input *head, char *env_path)
{
	int		fd[2];
	int		prev_pipe;
	t_input	*current;

	prev_pipe = 0;
	current = head;
	while (current)
	{
		if (has_next_cmd(current))
			pipe(fd);
		else
		{
			fd[0] = -1;
			fd[1] = -1;
		}
		if (handle_parent_builtin(data, current))
		{
			current = get_next_command(current);
			continue ;
		}
		handle_fork(data, &prev_pipe, &current, fd, env_path);
	}
	wait_all(data);
	data->child_pid = -1;
}
