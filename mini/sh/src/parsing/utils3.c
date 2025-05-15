/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:29:52 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/15 18:42:31 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_env_var_into_array(char *input, char **array_ptr, int *k, int *j)
{
	char	*expanded;
	int		l;

	expanded = handle_env_variable(input, k);
	if (expanded && expanded[0] != '\0')
	{
		l = 0;
		while (expanded[l])
		{
			(*array_ptr)[*j] = expanded[l];
			(*j)++;
			l++;
		}
	}
	free(expanded);
}
