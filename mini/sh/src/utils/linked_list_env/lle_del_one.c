/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_del_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:57:57 by afloras           #+#    #+#             */
/*   Updated: 2025/04/04 12:36:59 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Deletes a single node in the linked list of environment variables.
/// @param env Pointer to the environment variable node to delete.
/// @param del Function pointer to a function that frees the content of the node.
/// @example lle_del_one(node, free);
void	lle_del_one(t_env *env, void (*del)(void *))
{
	if (!env)
		return ;
	if (del)
	{
		(*del)(env->name);
		(*del)(env->value);
	}
	free(env);
}
