/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:13:15 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 21:49:22 by monoguei         ###   ########.fr       */
=======
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:13:15 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/11 18:16:27 by lylrandr         ###   ########.fr       */
>>>>>>> export
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	b_env(t_data* data)
{
	t_input *current;

	current = data->input;
<<<<<<< HEAD
	while (current->next && current->next->type != T_OP && current->next->type != T_PIPE)
	{
		current = current->next;
		if (ft_strncmp_end(current->token, "env", 4) != 0)
=======
	while (current->next)
	{
		current = current->next;
		if (ft_strncmp_end(current->token, "env", 3) != 0)
>>>>>>> export
		{
			ft_printf_stderr("env: '%s': No such file or directory\n", current->token);
			return ;
		}
	}
	print_lle(data);
}
<<<<<<< HEAD
=======

/*
tests
	env
	print env ok

	env env
	print 1x env.

	env hola
	"env: ʻhola’: No such file or directory
*/
>>>>>>> export
