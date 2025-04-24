/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:38:25 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/24 18:22:20 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	redir(t_input *current)
{
	while (current)
	{
		if (current->type == T_OP)
		{
			if (!current->token || !current->next || !current->next->token)
				break;
			if (!ft_strncmp(current->token, ">>", 3))
				heredoc_append(current);
			else if (!ft_strncmp(current->token, "<<", 3))
				heredoc(current);
			else if (!ft_strncmp(current->token, ">", 2) || !ft_strncmp(current->token, "<", 2))
				simple_redir(current);
		}
		current = current->next;
	}
}


void	heredoc(t_input *current)
{
	int		hd_pipe[2];
	char	*del;
	char	*line;

	del = current->next->token;
	pipe(hd_pipe);
	while (1)
	{
		line = readline("> ");
		if ((ft_strlen(line) != 0) && ft_strncmp(line, del, ft_strlen(line)) == 0)
			break;
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free(line);
	}
	close(hd_pipe[1]);
	dup2(hd_pipe[0], 0);
	close(hd_pipe[0]);
}

void	simple_redir(t_input *current)
{
	int	fd;

	if ((ft_strncmp(current->token, ">", 1) == 0) && current->next)
	{
		fd = open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
		return;
	}
	else if ((ft_strncmp(current->token, "<", 1) == 0) && current->next)
	{
		fd = open(current->next->token, O_RDONLY);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(fd, 0);
		close(fd);
	}
}

void	heredoc_append(t_input *current)
{
	int	fd;

	if ((ft_strncmp(current->token, ">>", 2) == 0) && current->next)
	{
		fd = open(current->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		dup2(fd, 1);
		close(fd);
	}
	else
		heredoc(current);
}
