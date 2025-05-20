/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/20 21:59:52 by monoguei         ###   ########.fr       */
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
	t_input	*curr = current->next;
	int		n_flag = OFF;
	int		first = 1;

	while (curr && is_n_flag(curr->token))
	{
		n_flag = ON;
		curr = curr->next;
	}
	while (curr && curr->type != T_PIPE)
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
