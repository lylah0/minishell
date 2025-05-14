/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:18:44 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/06 16:26:36 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	has_redirection(t_input *current)
{
	while (current)
	{
		if (current->type == T_OP)
			return true;
		current = current->next;
	}
	return false;
}

bool	is_safe_to_exec_in_parent(t_input *current)
{
	t_input *tmp = current;

	if (!tmp)
		return (false);
	while (tmp)
	{
		if (tmp->type == T_PIPE || tmp->type == T_OP)
			return (false);
		tmp = tmp->next;
	}
	return (true);
}
