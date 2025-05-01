/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_search_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:07:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/25 11:19:43 by monoguei         ###   ########.fr       */
=======
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:07:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/01 14:42:33 by monoguei         ###   ########.fr       */
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
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
<<<<<<< HEAD
	while (current != NULL && ft_strcmp(current->name, name) != 0)
=======
	while (current != NULL && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
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
<<<<<<< HEAD
char *search_env_value_safe(t_env *env, const char *name)
=======
char *search_env_value_safe(t_env *env, char *name)
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
{
	t_env *var = search_env_name(env, name);
	if (!var || !var->value)
		return NULL;
	return var->value;
<<<<<<< HEAD
}
=======
}
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
