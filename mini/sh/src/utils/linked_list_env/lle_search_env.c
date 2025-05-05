/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_search_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:07:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/05 17:53:02 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Recherche une variable d'environnement par son nom dans une liste chaînée.
/// @param env Pointeur vers la tête de la liste chaînée des variables d'environnement.
/// @param name Le nom de la variable d'environnement à rechercher.
/// @return Un pointeur vers la structure t_env correspondant à la variable trouvée, ou NULL si elle n'existe pas.
t_env	*search_env_name(t_env *env, char *name)
{
	t_env	*current;
	t_env	**return_env;

	current = env;
	while (current != NULL && ft_strncmp(current->name, name, ft_strlen(name)) != 0)
		current = current->next;
	if (current == NULL)
		return (NULL);
	return_env = &current;
	return (*return_env);
}
/// @brief Recherche la valeur d'une variable d'environnement de manière sécurisée.
/// @param env Pointeur vers la tête de la liste chaînée des variables d'environnement.
/// @param name Le nom de la variable d'environnement à rechercher.
/// @return La valeur de la variable d'environnement si elle existe et est définie, NULL sinon.
char *search_env_value_safe(t_env *env, char *name)
{
	t_env *var = search_env_name(env, name);
	if (!var || !var->value)
		return NULL;
	return var->value;
}
