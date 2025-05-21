/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:04:43 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define TRUE 1
#define FALSE 0

void	exit_no_arg(t_data *data, int in_pipe)
{
	if (!in_pipe)
		ft_putstr_fd("exit\n", 1);
	data->should_exit = 1;
}

void	exit_n(t_data *data, char *num)
{
	int	n;

	n = (ft_atoi(num) % 256 + 256) % 256;
	ft_putstr_fd("exit\n", 1);
	data->exit_code = n;
	data->should_exit = 1;
}

void	exit_alpha(t_data *data, char *word)
{
	ft_putstr_fd("exit\n", 1);
	ft_printf_stderr("minishell: exit: %s: numeric argument required\n", word);
	data->exit_code = 2;
	data->should_exit = 1;
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
	else if (next_token && next_token->next && next_token->next->type != T_PIPE
		&& next_token->next->type != T_OP)
		exit_multiple_arg(data);
	else if (str_isdigit(next_token->token) == FALSE)
		exit_alpha(data, next_token->token);
}
