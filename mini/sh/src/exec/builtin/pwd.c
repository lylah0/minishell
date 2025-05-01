/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:34:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/01 14:40:52 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in print working directory `pwd`
/// @param  
void	b_pwd(t_data *data)
{
	t_env *current;

	// ft_putendl_fd(getcwd(NULL, 0), 1);

	current = search_env_name(data->env, "PWD");
	if (!current)
	{
		perror("pwd");
		return;
	}
	printf("%s\n", current->value);
}