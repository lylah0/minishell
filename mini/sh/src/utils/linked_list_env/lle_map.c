/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:07 by afloras           #+#    #+#             */
/*   Updated: 2025/04/04 12:35:16 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Maps a function over a linked list of environment variables.
/// @param env The linked list of environment variables to map over.
/// @param f The function to apply to each element's name and value.
/// @param del The function to delete elements in case of failure.
/// @return A new linked list with the mapped elements, or NULL on failure.
/// @example t_env *new_env = lle_map(env, my_transform_function, my_delete_function);
t_env	*lle_map(t_env *env, void *(*f)(void *), void (*del)(void *))
{
	t_env	*env_src;
	t_env	*env_new;
	t_env	*env_final;
	void	*temp_name;

	if (!env || !f || !del)
		return (0);
	env_src = env;
	env_final = 0;
	while (env_src)
	{
		temp_name = (*f)(env_src->name);
		temp_name = (*f)(env_src->value);
		env_new = lle_new(temp_name);
		if (!env_new)
		{
			(*del)(temp_name);
			lle_clear(&env_final, del);
			return (0);
		}
		lle_add_back(&env_final, env_new);
		env_src = env_src->next;
	}
	return (env_final);
}
