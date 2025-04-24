/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 18:12:43 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/23 17:14:56 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	is_parent_builtin(char *token)
{
	if (!ft_strncmp(token, "cd", 3)
		|| !ft_strncmp(token, "export", 7)
		|| !ft_strncmp(token, "unset", 6)
		|| !ft_strncmp(token, "exit", 5))
		return (1);
	return (0);
}

