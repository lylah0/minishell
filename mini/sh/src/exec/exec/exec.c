/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:36:38 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/16 15:15:10 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	**build_cmd_arg(t_input *token)
{
	char	**cmd;
	int		count;

	count = count_args(token);
	cmd = malloc(sizeof(char *) * (count + 1));
	if (!cmd)
		return (NULL);
	cmd[0] = ft_strdup(token->token);
	fill_cmd_args(cmd, token);
	return (cmd);
}

void	exec(t_data *data, t_input *current, char *env_path, int in_pipe)
{
	char	**cmd;
	char	*cmd_path;

	if (!current)
		return;
	if (is_builtin(current->token))
	{
		kind_of_token(data, current, in_pipe);
		exit(0);
	}
	cmd = build_cmd_arg(current);
	cmd_path = get_path(env_path, cmd[0]);
	if (!cmd_path)
	{
		ft_printf_stderr("minishell: command not found: %s\n", cmd[0]);
		exit(127);
	}
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
