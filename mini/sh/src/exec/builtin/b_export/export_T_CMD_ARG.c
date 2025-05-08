/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/08 20:33:02 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	add_env_name(t_data *data, char *env_name)
{
	t_env	*new_node;
	
	if (!data || !env_name)
		return;
	if (search_env_name(data->env, env_name) == NULL)// si cette var n'existe pas
	{
		new_node = lle_new(env_name, NULL);
		lle_add_back(&data->env, new_node);
	}	
}
void	add_new_env_var_and_value(t_data *data, char *env_name, char *env_value)
{
	t_env	*new_node;
	
	if (!data || !env_name || !env_value)
		return;
	if (search_env_name(data->env, env_name) == NULL)// si cette var n'existe pas
	{
		new_node = lle_new(env_name, env_value);
		lle_add_back(&data->env, new_node);
	}
}
// void	update_env_value(t_data *data, char *env_name, char *env_value)
// {
// 	t_env	*node_to_update;
	
// 	if (!data || !env_name || !env_value)
// 		return;
// 	node_to_update = search_env_name(data->env, env_name);// si cette var n'existe pas
// 	free(node_to_update->value);
// 	node_to_update->value = env_value;
// }