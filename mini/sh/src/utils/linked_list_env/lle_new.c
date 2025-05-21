/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:17 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 16:50:12 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static char	*dup_or_null(const char *str)
{
	if (str == NULL)
		return (NULL);
	return (strdup(str));
}

static void	free_env_fields(t_env *env)
{
	if (env)
	{
		free(env->name);
		free(env->value);
		free(env);
	}
}

t_env	*lle_new(char *name, char *value)
{
	t_env	*new_list;

	new_list = malloc(sizeof(t_env));
	if (!new_list)
		return (NULL);
	new_list->name = dup_or_null(name);
	if (!new_list->name)
	{
		free(new_list);
		return (NULL);
	}
	new_list->value = dup_or_null(value);
	if (value && !new_list->value)
	{
		free_env_fields(new_list);
		return (NULL);
	}
	new_list->next = NULL;
	return (new_list);
}
