/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:17 by monoguei           #+#    #+#             */
/*   Updated: 2025/04/04 12:35:39 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Creates a new environment variable node with the given name.
/// @param name The name to be assigned to the new environment variable node.
/// @return A pointer to the newly created t_env node, or NULL if allocation fails.
t_env	*lle_new(void *name)
{
	t_env	*new_list;

	new_list = (t_env *) malloc(sizeof(t_env));
	if (!new_list)
		return (0);
	new_list->name = name;
	new_list->next = 0;
	return (new_list);
}
