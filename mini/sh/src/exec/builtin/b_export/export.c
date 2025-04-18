/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/18 16:00:20 by lylrandr         ###   ########.fr       */
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
		printf("export.c > b_export : \t export tout nu, input = T_CMD\n");
	}
	else if (data->input->type == 1)
	{
		if (is_valid_env_var_syntax(data->input->next->token) == TRUE)
		{
			add_env_var(data, data->input->next->token);// add ou maj NAME=value
		}
		printf("export.c > b_export : \t export avec arg, input = T_CMD_ARG + T_ARG\n");
	}
	else
		return ;
}
