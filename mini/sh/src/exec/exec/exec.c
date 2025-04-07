/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:36:38 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/07 15:38:17 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**build_cmd_arg(t_input *token)
{
	t_input	*tmp;
	int		i;
	char	**cmd;

	tmp  = token;
	i = 0;
	while (tmp && tmp->type != T_PIPE && tmp->type != T_OP)
	{
		i++;
		tmp = tmp->next;
	}
	cmd = malloc(sizeof(char *) * (i + 1));
	if (!cmd)
		return (NULL);
	tmp = token;
	i = 0;
	while (tmp && tmp->type != T_PIPE && tmp->type != T_OP)
	{
		cmd[i] = ft_strdup(tmp->token);
		i++;
		tmp = tmp->next;
	}
	cmd[i] = NULL;
	return (cmd);
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
