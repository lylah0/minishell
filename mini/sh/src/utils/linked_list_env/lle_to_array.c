/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:07:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:11:57 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	lle_to_array(t_data *data)
{
	char	**copy_env;
	t_env	*current;
	int		index_array;

	(void)copy_env;
	index_array = 0;
	current = data->env;
	data->copy_env = malloc(sizeof(char *) * (lle_size(current) + 1));
	if (!data->copy_env)
		return ;
	while (current)
	{
		data->copy_env[index_array] = strjoin_name_equal_value(current->name,
				current->value);
		index_array++;
		current = current->next;
	}
	data->copy_env[index_array] = NULL;
}
