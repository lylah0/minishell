/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:52:37 by lylrandr          #+#    #+#             */
/*   Updated: 2025/03/27 17:53:32 by lylrandr         ###   ########.fr       */
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

	path = ft_get_env_path(env);
	if (!path)
		return (0);
	executable = ft_get_path(path, token);
	free(path);
	if (executable)
	{
		free(executable);
		return (1);
	}
	return (0);
}
