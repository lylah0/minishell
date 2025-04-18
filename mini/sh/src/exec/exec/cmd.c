/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:37:28 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/18 17:32:16 by monoguei         ###   ########.fr       */
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

void	exec_child(int prev_pipe, t_input *current, int fd[2], char *env_path, t_data *data)
{
	char	**cmd;
	char	*cmd_path;

	(void)data;
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
	if (is_builtin(current->token))
	{
		kind_of_token(data, current);
		exit(0);
	}
	cmd = build_cmd_arg(current);
	cmd_path = get_path(env_path, cmd[0]);
	execve(cmd_path, cmd, NULL);
	printf("minishell: command not found: %s\n", cmd[0]);
	exit(127);
}

void	exec_parent(int *prev_pipe, t_input **current, int fd[2])
{
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
		pid = fork();
		if (pid == 0)
			exec_child(prev_pipe, current, fd, env_path, data);
		else
			exec_parent(&prev_pipe, &current, fd);
	}
	wait_all();
}
