/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:29:52 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/16 14:57:48 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_env_var_into_array(t_data *data, char *input, char **array_ptr, int *k, int *j)
{
	char	*expanded;
	int		l;

	expanded = handle_env_variable(data, input, k);
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
