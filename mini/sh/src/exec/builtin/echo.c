/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:04:14 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static int	is_n_flag(char *token)
{
	int	i;

	if (!token || token[0] != '-' || token[1] != 'n')
		return (0);
	i = 2;
	while (token[i] == 'n')
		i++;
	return (token[i] == '\0');
}

static void	print_echo_args(t_input *curr, int *first)
{
	if (curr->token != NULL)
	{
		if (!*first)
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, curr->token, ft_strlen(curr->token));
		*first = 0;
	}
}

void	b_echo(t_data *data, t_input *current)
{
	t_input	*curr;
	int		n_flag;
	int		first;

	curr = current->next;
	n_flag = OFF;
	first = 1;
	while (curr && is_n_flag(curr->token))
	{
		n_flag = ON;
		curr = curr->next;
	}
	while (curr && curr->type != T_PIPE && curr->type != T_OP)
	{
		if (curr->type == T_OP || curr->type == T_SKIP)
		{
			curr = curr->next;
			continue ;
		}
		print_echo_args(curr, &first);
		curr = curr->next;
	}
	if (n_flag == OFF)
		write(STDOUT_FILENO, "\n", 1);
	data->exit_code = 0;
	exit(0);
}
