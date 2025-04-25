/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/25 17:06:28 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void    b_export(t_data *data)
{
	if (data->input->type == 0)// `export`[ ] et la suite est .. ?
	{
		create_env_copy_array(data);
		sort_words(data->copy_env, get_array_length(data->copy_env));
		print_copy_env(data);
	}
	else if (data->input->type == 1)
	{
		if (is_valid_env_var_syntax(data->input->next->token) == TRUE)
			add_env_var(data, data->input->next->token);// add ou maj NAME=value
	}
	else
		return ;
}
