/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:12:41 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 21:29:55 by monoguei         ###   ########.fr       */
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
