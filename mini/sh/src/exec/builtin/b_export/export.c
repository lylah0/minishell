/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/06 16:42:41 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

void	b_export(t_data *data)
{
	t_input	*curr;

	curr = data->input->next;
	if (!curr)
	{
		create_env_copy_array(data);
		sort_words(data->copy_env, get_array_length(data->copy_env));
		print_copy_env(data);
		return ;
	}
	while (curr && curr->type != T_PIPE)
	{
		if (is_valid_env_var_syntax(curr->token))
			add_env_var(data, curr->token);
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(curr->token, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			exit_code = 1;
		}
		curr = curr->next;
	}
}
