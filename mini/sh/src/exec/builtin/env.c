/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:13:15 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/12 19:33:22 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	b_env(t_data* data)
{
	t_input *current;

	current = data->input;
	while (current->next)
	{
		current = current->next;
		if (ft_strncmp_end(current->token, "env", 3) != 0)
		{
			ft_printf_stderr("env: '%s': No such file or directory\n", current->token);
			return ;
		}
	}
	print_lle(data);
}
