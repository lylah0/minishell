/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:36:38 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/01 16:08:21 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**build_cmd_arg(t_input *token)
{
	t_input	*tmp;
	int		i = 0;
	char	**cmd;

	tmp = token;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type != T_OP && (tmp->prev == NULL || tmp->prev->type != T_OP))
			i++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	tmp = token;
	i = 0;
	while (tmp && tmp->type != T_PIPE)
	{
		if (tmp->type != T_OP && (tmp->prev == NULL || tmp->prev->type != T_OP))
		{
			cmd[i] = ft_strdup(tmp->token);
			i++;
		}
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
}


void	exec(t_input *current, t_data *data, char *env_path)
{
	char	**cmd;
	char	*cmd_path;

	if (is_builtin(current->token))
	{
		kind_of_token(data, current);
		if (current->next->next->type == T_PIPE)
		{
			current = current->next;
			exec(current, data, env_path);
		}
		else
			exit(0);
	}
	cmd = build_cmd_arg(current);
	cmd_path = get_path(env_path, cmd[0]);
	execve(cmd_path, cmd, NULL);
	printf("minishell: command not found: %s\n", cmd[0]);
	exit(127);
}

int	count_cmd(t_input *head)
{
	int count = 0;
	t_input *curr = head;

	while (curr)
	{
		if (curr->type == T_CMD || curr->type == T_CMD_ARG)
		{
			count++;
			while (curr && curr->type != T_PIPE)
				curr = curr->next;
		}
		else
			curr = curr->next;
	}
	return (count);
}
