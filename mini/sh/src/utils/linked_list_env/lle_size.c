/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:28 by afloras           #+#    #+#             */
/*   Updated: 2025/05/06 15:01:28 by monoguei         ###   ########.fr       */
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
