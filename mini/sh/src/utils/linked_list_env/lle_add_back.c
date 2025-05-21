/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_add_back.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:57:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:11:03 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Adds a new node to the end of the linked list.
/// @param env Pointer to the head of the linked list.
/// @param new1 The new node to be added to the linked list.
void	lle_add_back(t_env **env, t_env *new1)
{
	t_env	*env_last;

	if (!new1)
		return ;
	env_last = lle_last(*env);
	if (!env_last)
		*env = new1;
	else
		env_last->next = new1;
}
