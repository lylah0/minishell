/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:52:37 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/13 17:15:19 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_input *filter_args(t_input *args)
{
	t_input *filtered = NULL;
	t_input **tail = &filtered;

	while (args)
	{
		if (args->type == T_OP && args->next)
		{
			args = args->next->next;
			continue;
		}
		if (args->type == T_ARG || args->type == T_WORD)
		{
			*tail = args;
			tail = &args->next;
		}
		args = args->next;
	}
	*tail = NULL;
	return filtered;
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
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else
		return (0);
}

char	*my_getenv(t_data *data, char *var_name)
{
	while (data->env->next && !(ft_strncmp(data->env->name, var_name, ft_strlen(var_name)) == 0
		&& data->env->name[ft_strlen(var_name)] == '\0'))
		data->env = data->env->next;
	if (ft_strncmp(data->env->name, var_name, ft_strlen(data->env->name)) == 0)
		return (data->env->value);
	else
		return (NULL);
}

bool	in_quotes(char *str, int index)
{
	bool	in_single;
	bool	in_double;
	int		i;

	i = 0;
	in_single = false;
	in_double = false;
	while (i < index && str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return in_double;
}
