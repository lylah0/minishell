/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/16 14:48:14 by monoguei         ###   ########.fr       */
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
	data->exit_code = 1;
	data->exit_status = 0;
	if (data->input->type == T_CMD_ARG)
	{
		printf("T_CMD_ARG\n");
		char *arg;
		arg = data->input->next->token;
		if (!data->input->next->next)
		{
			if (ft_str_isdigit(arg) == 1)
			{
				printf("exit\n");
				exit(ft_atoi(arg) % 256);
			}
			else
			{
				printf("`bash: exit: %s: numeric argument required`\n", arg);
				exit(255);
			}
		}
		else
		{
			printf("`bash: exit: too many arguments`\n");
			data->exit_status = 1;
		}
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}

// `echo $?` pour tester dans le terminal et obtenir le data->exit_code
// [ ] si exit dans pipe !!! ca ne quitte pas le term !!!
// [ ] free proprement ce quil faut !!!
