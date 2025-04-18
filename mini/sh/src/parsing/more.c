/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:52:37 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/18 17:52:53 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_exit_code(void)
{
	printf("get exit code");
}

int	is_cmd(char *token, char **env)
{
	char	*path;
	char	*executable;

	path = get_env_path(env);
	if (!path)
		return (0);
	executable = get_path(path, token);
	free(path);
	if (executable)
	{
		free(executable);
		return (1);
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else
		return (0);
}

void	first_word(char **input, char **env)
{
	char	*env_path;
	char	*cmd_path;

	env_path = get_env_path(env);
	cmd_path = get_path(env_path, input[0]);
	//	free(env_path);
	if (!cmd_path)
	{
		printf("minishell: command not found: %s\n", input[0]);
		return ;
	}
	// printf("\ncmd found\n");
}
