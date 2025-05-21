/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:33:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 16:56:28 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_lle(t_data *data)
{
	t_env	*temp;

	temp = NULL;
	while (data->env)
	{
		temp = data->env->next;
		free(data->env->name);
		free(data->env->value);
		free(data->env);
		data->env = temp;
	}
}

void	print_lle(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		printf("%s", current->name);
		if (current->value)
			printf("=%s\n", current->value);
		else
			printf("\n");
		current = current->next;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = tmp;
	}
}

static void	fill_env_node(t_env *node, const char *env)
{
	char	*separator;

	separator = ft_strchr(env, '=');
	if (separator)
	{
		node->name = ft_substr(env, 0, separator - env);
		node->value = ft_strdup(separator + 1);
	}
	else
	{
		node->name = ft_strdup(env);
		node->value = NULL;
	}
}

static t_env	*create_env_node(const char *env)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	fill_env_node(node, env);
	node->next = NULL;
	if (!node->name || (ft_strchr(env, '=') && !node->value))
	{
		free(node->name);
		free(node->value);
		free(node);
		return (NULL);
	}
	return (node);
}
