/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/16 15:08:26 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define TRUE 1
#define FALSE 0

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
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

void	exit_no_arg(t_data *data, int in_pipe)
{
	if (!in_pipe)
		ft_putstr_fd("exit\n", 1); // Only print when not in a pipeline
	exit(data->exit_code);
}

void	exit_n(t_data *data, char *num)
{
	int	n;

	n = (ft_atoi(num) % 256 + 256) % 256;
	ft_putstr_fd("exit\n", 1);
	data->exit_code = n;
	exit(data->exit_code);
}

void	exit_alpha(t_data *data, char *word)
{
	ft_putstr_fd("exit\n", 1);
	ft_printf_stderr("minishell: exit: %s: numeric argument required\n", word);
	data->exit_code = 2;
	exit(data->exit_code);
}

void	exit_multiple_arg(t_data *data)
{
	ft_printf_stderr("minishell: exit: too many arguments\n");
	data->exit_code = 1;
}

void	b_exit(t_data *data, t_input *current, int in_pipe)
{
	t_input	*next_token;

	(void)data;
	next_token = current->next;
	if (!next_token || next_token->type == T_PIPE || next_token->type == T_OP)
		exit_no_arg(data, in_pipe);
	else if (str_isdigit(next_token->token) == TRUE && (!next_token->next
			|| next_token->next->type == T_PIPE
			|| next_token->next->type == T_OP))
		exit_n(data, next_token->token);
	else if (str_isdigit(next_token->token) == TRUE && next_token->next
		&& next_token->next->type != T_PIPE && next_token->next->type != T_OP)
		exit_multiple_arg(data);
	else if (str_isdigit(next_token->token) == FALSE)
		exit_alpha(data, next_token->token);
}
