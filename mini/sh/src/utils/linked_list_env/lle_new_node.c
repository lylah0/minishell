/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_new_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:30:50 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 21:36:49 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*create_env_node(const char *env)
{
	t_env	*node;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	split_env(env, &name, &value);
	if (!name || (ft_strchr(env, '=') && !value))
	{
		free(name);
		free(value);
		free(node);
		return (NULL);
	}
	node->name = name;
	node->value = value;
	node->next = NULL;
	return (node);
}
