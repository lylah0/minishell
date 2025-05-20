/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:40 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/20 22:03:49 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void unset_env_var(t_env **env, char *name)
{
	if (search_env_name(*env, name))
		lle_del_one(env, name);
}

static void init_empty_env(t_data *data)
{
	printf("Aucune variable d'environnement\n");
	printf("Initialisation d'un environnement vide...\n");
	data->env = malloc(sizeof *data->env);
	if (data->env)
	{
		data->env->name = ft_strdup("Head_of_environnement");
		data->env->value = NULL;
		data->env->next = NULL;
	}
}

void b_unset(t_data *data)
{
	t_input *current;

	if (!data || !data->input || !data->input->next)
		return;
	if (!data->env)
	{
		init_empty_env(data);
		return;
	}
	current = data->input->next;
	while (current)
	{
		if (current->type == T_WORD)
			unset_env_var(&data->env, current->token);
		else if (current->type != T_SKIP)
			break;
		current = current->next;
	}
}
