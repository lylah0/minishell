/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:17 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:11:49 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*lle_new(char *name, char *value)
{
	t_env	*new_list;

	new_list = malloc(sizeof(t_env));
	if (!new_list)
		return (NULL);
	new_list->name = strdup(name);
	if (!new_list->name)
	{
		free(new_list);
		return (NULL);
	}
	if (value == NULL)
	{
		new_list->value = NULL;
	}
	else
	{
		new_list->value = strdup(value);
		if (!new_list->value)
		{
			free(new_list->name);
			free(new_list);
			return (NULL);
		}
	}
	new_list->next = NULL;
	return (new_list);
}
