/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/03 14:46:07 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Checks if a string contains only numeric characters, optionally preceded by a sign.
/// @param str The string to check.
/// @return 1 if the string is numeric, 0 otherwise.
int	ft_str_isdigit(const char *str)
{
	int i = 0;

	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

/// @brief built-in `exit` `exit N` `exit arg` `exit arg1 arg2`
/// @param data The structure containing input and exit status information.
void	b_exit(t_data *data)
{
	// data->should_exit = 1;
	// data->exit_status = 0;
	if (data->input->type == T_CMD_ARG)
	{
		char *arg;
		arg = data->input->next->token;
		if (!data->input->next->next)
		{
			if (ft_str_isdigit(arg) == 1)
			{
				data->exit_status = ft_atoi(arg) % 256;
				exit(data->exit_status);
			}
			else
			{	
				ft_putstr_fd(" numeric argument required\n", 2);
				// exit(255);
				data->exit_status = 2;
				exit(data->exit_status);
			}
		}
		else
		{
			ft_putstr_fd(" too many arguments\n", 2);
			data->exit_status = 1;
		}
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		exit(data->exit_status);
	}
}

// `echo $?` pour tester dans le terminal et obtenir le exit_code
// [ ] si exit dans pipe !!! ca ne quitte pas le term !!!
// [ ] free proprement ce quil faut !!!


