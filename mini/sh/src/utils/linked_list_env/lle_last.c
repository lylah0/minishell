/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_last.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:58:54 by afloras           #+#    #+#             */
/*   Updated: 2025/04/04 12:32:27 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Returns the last node of the linked list.
/// @param env The head of the linked list.
/// @return The last node of the linked list, or NULL if the list is empty.
t_env	*lle_last(t_env *env)
{
	t_env	*env_last;

	if (!env)
		return (0);
	env_last = env;
	while (env_last->next)
		env_last = env_last->next;
	return (env_last);
}
