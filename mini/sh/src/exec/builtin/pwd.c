/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:34:51 by monoguei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/01 15:10:21 by monoguei         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2025/04/25 11:17:24 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/05/01 14:40:52 by monoguei         ###   ########.fr       */
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
>>>>>>> eb617a4c514e795db0ef1fe9f6c22ce25ebbf2de
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in print working directory `pwd`
/// @param  
void	b_pwd(t_data *data)
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