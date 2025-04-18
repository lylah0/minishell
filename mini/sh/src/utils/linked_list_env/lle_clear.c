/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:57:46 by monoguei           #+#    #+#             */
/*   Updated: 2025/04/04 12:33:12 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Clears the entire linked list of environment variables.
/// @param env Pointer to the head of the linked list.
/// @param del Function pointer to delete the content of a node.
void	lle_clear(t_env **env, void (*del)(void *))
{
	t_env	*env_temp;

	if (!*env)
		return ;
	while (*env)
	{
		env_temp = (*env)->next;
		lle_del_one(*env, del);
		*env = env_temp;
	}
}
