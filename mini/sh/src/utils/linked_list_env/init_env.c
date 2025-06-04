/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:33:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/06/04 18:16:50 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	split_env(const char *env, char **name, char **value)
{
	char	*sep;

	sep = ft_strchr(env, '=');
	if (sep)
	{
		*name = ft_substr(env, 0, sep - env);
		*value = ft_strdup(sep + 1);
	}
	else
	{
		*name = ft_strdup(env);
		*value = NULL;
	}
}

t_env	*create_lle(t_data *data, char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*node;
	int		i;

	i = 0;
	head = NULL;
	tail = NULL;
	while (envp[i])
	{
		node = create_env_node(envp[i]);
		if (!node)
		{
			free_lle(data);
			return (NULL);
		}
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		i++;
	}
	return (head);
}

void	init_env(t_data *data, char **envp)
{
	data->env = create_lle(data, envp);
	if (!envp)
	{
		data->env = malloc(sizeof * data->env);
		data->env->name = NULL;
		data->env->value = NULL;
		data->env->next = NULL;
		return ;
	}
}
