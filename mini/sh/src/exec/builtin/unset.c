/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:40 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/11 18:16:13 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void b_unset(t_data *data)
{
	t_input *current;

	if (!data || !data->input)
		return;

	current = data->input->next;
	while (current)
	{
		lle_del_one(&data->env, current->token);
		current = current->next;
	}
}
