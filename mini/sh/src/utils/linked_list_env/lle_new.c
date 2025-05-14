/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:17 by monoguei           #+#    #+#             */
/*   Updated: 2025/05/11 17:18:36 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env *lle_new(char *name, char *value)
{
	t_env *new_list = malloc(sizeof(t_env));
	if (!new_list)
		return NULL;

	// Attribution de name
	new_list->name = strdup(name);
	if (!new_list->name)
	{
		free(new_list);
		return NULL;
	}

	// Si value est NULL (export sans =), attribuer NULL à value
	if (value == NULL)  // Cas de export NAME
	{
		new_list->value = NULL;
	}
	else  // Cas de export NAME="" ou export NAME="valeur"
	{
		new_list->value = strdup(value);  // Copie de la valeur
		if (!new_list->value)
		{
			free(new_list->name);
			free(new_list);
			return NULL;
		}
	}

	new_list->next = NULL;
	return new_list;
}
