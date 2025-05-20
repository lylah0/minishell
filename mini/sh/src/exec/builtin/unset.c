/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:40 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/20 13:31:31 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void b_unset(t_data *data)
{
	t_input *current;

	if (!data || !data->input || !data->input->next)	
		return;
	if (!data->env)
	{
		printf("Aucune variable d'environnement\nInitialisation d'un environnement vide...\n");
		data->env         = malloc(sizeof *data->env);
        data->env->name   = ft_strdup("Head_of_environnement");
        data->env->value  = NULL;
        data->env->next   = NULL;
		return ;
	}
	current = data->input->next;
	(void)current;
	while (current->next)
	{
		if (current->type == T_WORD)
		{
			if (search_env_name(data->env, current->token))
				lle_del_one(&data->env, current->token);
		}
		else if (current->type == T_SKIP)
			current = current->next;
		else
			break ;
		if (search_env_name(data->env, current->token))
			lle_del_one(&data->env, current->token);
		current = current->next;
	}
}
