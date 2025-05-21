/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_new_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:13:41 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 19:36:17 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*create_lle_empty(t_env *env)
{
	t_env	*current;

	current = NULL;
	current = env;
	current = malloc(sizeof(t_env));
	if (!current)
	{
		free(current);
		return (0);
	}
	current->name = ft_strdup("");
	current->value = NULL;
	current->next = NULL;
	return (current);
}
