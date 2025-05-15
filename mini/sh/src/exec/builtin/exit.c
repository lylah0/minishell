/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 16:22:51 by lylrandr         ###   ########.fr       */
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

void	exit_no_arg(int in_pipe)
{
	if (!in_pipe)
		ft_putstr_fd("exit\n", 1); // Only print when not in a pipeline
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
	ft_printf_stderr("minishell: exit: %s: numeric argument required\n", word);
	exit_code = 2;
	exit(exit_code);
}

void	exit_multiple_arg(void)
{
	ft_printf_stderr("minishell: exit: too many arguments\n");
	exit_code = 1;
}

void	b_exit(t_data *data, t_input *current, int in_pipe)
{
	t_input	*next_token;

	(void)data;
	next_token = current->next;
	if (!next_token || next_token->type == T_PIPE || next_token->type == T_OP)
		exit_no_arg(in_pipe);
	else if (str_isdigit(next_token->token) == TRUE && (!next_token->next
			|| next_token->next->type == T_PIPE
			|| next_token->next->type == T_OP))
		exit_n(next_token->token);
	else if (str_isdigit(next_token->token) == TRUE && next_token->next
		&& next_token->next->type != T_PIPE && next_token->next->type != T_OP)
		exit_multiple_arg();
	else if (str_isdigit(next_token->token) == FALSE)
		exit_alpha(next_token->token);
}
