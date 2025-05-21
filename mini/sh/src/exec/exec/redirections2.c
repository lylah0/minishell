/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:18:44 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 21:42:54 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

bool	has_redirection(t_input *current)
{
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_OP)
			return (true);
		current = current->next;
	}
	return (false);
}

bool	is_safe_to_exec_in_parent(t_input *current)
{
	t_input	*tmp;

	tmp = current;
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

int	open_redirection_file(t_input *current)
{
	if (!ft_strncmp(current->token, ">>", 3))
		return (open(current->next->token, O_WRONLY | O_CREAT | O_APPEND,
				0644));
	else if (!ft_strncmp(current->token, ">", 2))
		return (open(current->next->token, O_WRONLY | O_CREAT | O_TRUNC, 0644));
	else if (!ft_strncmp(current->token, "<", 2))
		return (open(current->next->token, O_RDONLY));
	return (-2);
}
