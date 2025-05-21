/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:06:33 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:00:21 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_input	*get_next_command(t_input *node)
{
	while (node && node->type != T_PIPE)
		node = node->next;
	if (node && node->type == T_PIPE)
		return (node->next);
	return (NULL);
}
