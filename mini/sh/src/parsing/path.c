/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 18:11:17 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/22 14:11:09 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**split_path(char *fullpath)
{
	if (!fullpath)
		return (NULL);
	return (ft_split(fullpath, ':'));
}

char	*find_executable(char **path, char *cmd)
{
	int		i;
	char	*temp;
	char	*new_path;

	i = 0;
	if (!path)
		return (NULL);
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		new_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(new_path, X_OK) == 0)
		{
			free_tab(path);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	free_tab(path);
	return (NULL);
}

char	*get_path(char *fullpath, char *cmd)
{
	char	**path;

	path = split_path(fullpath);
	return (find_executable(path, cmd));
}

char	*get_env_path(char **env)
{
	int		i;
	char	**path;
	char	*result;

	i = 0;
	while (env[i])
	{
		path = ft_split(env[i], '=');
		if (!path)
			return (NULL);
		if (ft_strncmp_end(path[0], "PATH", 4) == 0)
		{
			result = ft_strdup(path[1]);
			free_tab(path);
			return (result);
		}
		free_tab(path);
		i++;
	}
	return (NULL);
}


