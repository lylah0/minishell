/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:13:15 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/22 17:05:02 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in env `env`
/// @param data 
void	b_env(t_data *data)
{
	t_env *current;
	
	current = (t_env *)data->env;
	while (current)
	{
		printf("%s=%s\n", current->name, current->value);// ft_str_fd plutot ?
		current = current->next;
	}
}