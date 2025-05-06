/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:58:08 by afloras           #+#    #+#             */
/*   Updated: 2025/04/04 12:37:57 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Iterates through a linked list of environment variables and applies a function to each element.
/// @param env Pointer to the head of the linked list of environment variables.
/// @param f Function pointer to apply to each element's name and value.
/// @example lle_iter(env_list, print_env_var);
void	lle_iter(t_env *env, void (*f)(void *))
{
	t_env	*env_temp;

	if (!env || !f)
		return ;
	env_temp = env;
	while (env_temp)
	{
		(*f)(env_temp->name);
		(*f)(env_temp->value);
		env_temp = env_temp->next;
	}
}
