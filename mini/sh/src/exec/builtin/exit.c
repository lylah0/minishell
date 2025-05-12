/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/12 19:33:27 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define TRUE 1
#define FALSE 0

int str_isdigit(char *str)
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

void	exit_no_arg()
{
	ft_putstr_fd("exit\n", 1);
	exit(exit_code);
}

void	exit_n(char *num)
{
	int	n;

	n = (ft_atoi(num) % 256 + 256) % 256;
	ft_putstr_fd("exit\n", 1);
	exit_code = n;
	exit(exit_code);
}

void	exit_alpha(char *word)
{
	ft_putstr_fd("exit\n", 1);
	ft_printf_stderr("bash: exit: %s: numeric argument required\n", word);
	exit_code = 2;
	exit(exit_code);
}

void	exit_multiple_arg(void)
{
	ft_printf_stderr("bash: exit: too many arguments\n");
	ft_putstr_fd("exit\n", 1);
	exit_code = 1;
}

void	b_exit(t_data *data)
{
	// exit_code = 0;// est ce vraiment necessaire de mettre a zero ici, plutot dans la boucle dans l'init du main
	if (!data->input->next)// aucun argument
		exit_no_arg();
	else if (data->input->next)
	{
		if (str_isdigit(data->input->next->token) == TRUE && !data->input->next->next)// premier arg numerique, pas de suite
			exit_n(data->input->next->token);
		else if (str_isdigit(data->input->next->token) == TRUE && data->input->next->next)// premier arg numerique, 2eme argument quelquil soit
			exit_multiple_arg();
		else if (str_isdigit(data->input->next->token) == FALSE)
			exit_alpha(data->input->next->token);
	}
}
