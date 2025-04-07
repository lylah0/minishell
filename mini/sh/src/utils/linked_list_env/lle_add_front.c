/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_add_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:57:37 by afloras           #+#    #+#             */
/*   Updated: 2025/04/04 12:32:59 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Adds a new node to the front of the linked list.
/// @param env Pointer to the head of the linked list.
/// @param new1 The new node to be added to the front.
void	lle_add_front(t_env **env, t_env *new1)
{
	if (!new1)
		return ;
	new1->next = *env;
	*env = new1;
}
