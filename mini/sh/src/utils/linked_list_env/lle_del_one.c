/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_del_one.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:57:57 by afloras           #+#    #+#             */
/*   Updated: 2025/05/09 13:49:39 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void lle_del_one(t_env **env, char *env_to_del)
{
	t_env *current;
	t_env *prev;

	if (!env || !*env || !env_to_del)
		return;
	current = *env;
	prev = NULL;
	while (current)
	{
		if (strcmp(current->name, env_to_del) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->name);
			if (current->value)
				free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}
