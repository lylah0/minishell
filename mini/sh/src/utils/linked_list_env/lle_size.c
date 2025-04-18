/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:28 by monoguei           #+#    #+#             */
/*   Updated: 2025/04/18 19:07:38 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Calculates the size of a linked list of environment variables.
/// @param env Pointer to the head of the linked list.
/// @return The size of the linked list.
int	lle_size(t_env *env)
{
	int		size;
	t_env	*env_temp;

	if (!env)
		return (0);
	env_temp = env;
	size = 0;
	while (env_temp)
	{
		env_temp = env_temp->next;
		size++;
	}
	return (size);
}
