/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:33:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 16:56:06 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*create_lle_empty(t_env *env)
{
	t_env	*current;

	current = NULL;
	current = env;
	current = malloc(sizeof(t_env));
	if (!current)
	{
		free(current);
		return (0);
	}
	current->name = ft_strdup("");
	current->value = NULL;
	current->next = NULL;
	return (current);
}

void	init_env(t_data *data, char **envp)
{
	data->env = create_lle(envp);
	if (!data->env)
	{
		data->env = malloc(sizeof * data->env);
		data->env->name = NULL;
		data->env->value = NULL;
		data->env->next = NULL;
		return ;
	}
}
