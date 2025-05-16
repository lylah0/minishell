/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:38:25 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/16 21:30:17 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	redir(t_input *current, t_data *data)
{
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_OP)
		{
			if (!current->token || !current->next || !current->next->token)
				break ;
			if (!ft_strncmp(current->token, ">>", 3))
				heredoc_append(current, data);
			else if (!ft_strncmp(current->token, "<<", 3))
				heredoc(current);
			else if (!ft_strncmp(current->token, ">", 2)
				|| !ft_strncmp(current->token, "<", 2))
				simple_redir(current, data);
			current = current->next ? current->next->next : NULL;
		}
		else
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
		if ((ft_strlen(line) != 0) && ft_strncmp(line, del,
				ft_strlen(line)) == 0)
		{
			free(line);
			break ;
		}
		write(hd_pipe[1], line, ft_strlen(line));
		write(hd_pipe[1], "\n", 1);
		free(line);
	}
	close(hd_pipe[1]);
	dup2(hd_pipe[0], 0);
	close(hd_pipe[0]);
}

void	simple_redir(t_input *current, t_data *data)
{
	int	fd;

	if ((ft_strncmp(current->token, ">", 1) == 0) && current->next)
	{
		fd = open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, 1);
		close(fd);
		data->stdout_redir = 1;
	}
	else if ((ft_strncmp(current->token, "<", 1) == 0) && current->next)
	{
		fd = open(current->next->token, O_RDONLY);
		dup2(fd, 0);
		close(fd);
		data->stdin_redir = 1;
	}
}

void	heredoc_append(t_input *current, t_data *data)
{
	int	fd;

	if ((ft_strncmp(current->token, ">>", 2) == 0) && current->next)
	{
		fd = open(current->next->token, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, 1);
		close(fd);
		data->stdout_redir = 1;
	}
	else
		heredoc(current);
}

void	validate_redirections(t_data *data, t_input *current)
{
	int	fd;

	while (current && current->type != T_PIPE)
	{
		if (current->type == T_OP && current->next)
		{
			fd = open_redirection_file(current);
			if (fd == -2)
			{
				current = current->next;
				continue ;
			}
			if (fd == -1)
			{
				ft_printf_stderr(current->next->token);
				perror(current->next->token);
				data->exit_code = 1;
				exit(1);
			}
			close(fd);
		}
		current = current->next;
	}
}
