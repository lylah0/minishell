/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_search_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:07:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/25 16:54:22 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Searches for an environment variable by name in a linked list.
/// @param env Pointer to the head of the linked list of environment variables.
/// @param name The name of the environment variable to search for.
/// @return A pointer to the t_env node containing the variable, or NULL if not found.
t_env	*search_env_name(t_env *env, char *name)
{
	t_env	*current;
	t_env	**return_env;

	current = env;
	while (current != NULL && ft_strcmp(current->name, name) != 0)
		current = current->next;
	if (current == NULL)
		return (NULL);
	return_env = &current;
	return (*return_env);
}

/// @brief Searches for an environment variable's value by name in a linked list.
/// @param env Pointer to the head of the linked list of environment variables.
/// @param name The name of the environment variable to search for.
/// @return The value of the environment variable as a string, or NULL if not found.
char *search_env_value_safe(t_env *env, const char *name)
{
	t_env *var = search_env_name(env, name);
	if (!var || !var->value)
		return NULL;
	return var->value;
}
