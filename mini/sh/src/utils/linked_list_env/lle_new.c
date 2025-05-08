/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:17 by afloras           #+#    #+#             */
/*   Updated: 2025/05/08 19:53:53 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// /// @brief Creates a new environment variable node with the given name.
// /// @param name The name to be assigned to the new environment variable node.
// /// @return A pointer to the newly created t_env node, or NULL if allocation fails.
// t_env	*lle_new(void *name)
// {
// 	t_env	*new_node;

// 	new_node = (t_env *) malloc(sizeof(t_env));
// 	if (!new_node)
// 		return NULL;
// 	new_node->name = ft_strdup(name);
// 	new_node->next = NULL;
// 	return (new_node);
// }

// /// @brief Creates a new environment variable node with the given name and value.
// /// @param name The name to be assigned to the new environment variable node.
// /// @param value The value to be assigned to the new environment variable node. Can be NULL.
// /// @return A pointer to the newly created t_env node, or NULL if allocation fails.
// t_env *lle_new(char *name, char *value)
// {
// 	t_env *new_node = malloc(sizeof(t_env));
// 	if (!new_node)
// 		return (NULL);

// 	new_node->name = strdup(name);
// 	if (!new_node->name)
// 	{
// 		free(new_node);
// 		return (NULL);
// 	}

// 	// if (value)
// 	// {
// 	// 	new_node->value = strdup(value);
// 	// 	if (!new_node->value)
// 	// 	{
// 	// 		free(new_node->name);
// 	// 		free(new_node);
// 	// 		return (NULL);
// 	// 	}
// 	// }
// 	// else
// 		new_node->value = NULL;

// 	new_node->next = NULL;
// 	return new_node;
// }

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
		printf("3, 2, 1...\n");
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

