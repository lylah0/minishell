/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:34:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/03 12:07:46 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in print working directory `pwd`
/// @param data Pointer to the data structure containing environment variables
void	b_pwd(t_data *data)
{
	t_env *current;

	current = search_env_name(data->env, "PWD");
	if (!current)
	{
		perror("pwd");
		return;
	}
	ft_printf("%s\n", current->value);
}
