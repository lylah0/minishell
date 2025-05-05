/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/05 22:47:05 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Checks if a string contains only numeric characters, optionally preceded by a sign.
/// @param str The string to check.
/// @return 1 if the string is numeric, 0 otherwise.
int	ft_str_isdigit(char *str)
{
	int	i = 0;

	if (!str || !str[0])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
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
	char	*arg;
	int		num;
	int		exit_val;

	data->should_exit = 1;
	if (data->input->next && (data->input->next->type == T_ARG || data->input->next->type == T_WORD))
	{
		arg = data->input->next->token;
		if (!data->input->next->next)
		{
			if (ft_str_isdigit(arg))
			{
				num = ft_atoi(arg);
				exit_val = (num % 256 + 256) % 256;
				printf("exit\n");
				exit_code = exit_val;
				exit(exit_code);
			}
			else
			{
				printf("exit\n");
				ft_putstr_fd("bash: exit: ", 2);
				ft_putstr_fd(arg, 2);
				ft_putendl_fd(": numeric argument required", 2);
				exit(2);
			}
		}
		else
		{
			ft_putstr_fd("bash: exit: too many arguments\n", 2);
			exit_code = 1;
			data->should_exit = 0;
			return;
		}
	}
	else
	{
		printf("exit\n");
		exit(0);
	}
}


// `echo $?` pour tester dans le terminal et obtenir le exit_code
// [ ] si exit dans pipe !!! ca ne quitte pas le term !!!
// [ ] free proprement ce quil faut !!!
