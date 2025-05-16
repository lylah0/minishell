/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/16 15:10:47 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define OFF 0
#define ON 1

int	n_option(t_input *input)
{
	t_input	*current;
	int		found;
	int		i;

	current = input->next;
	found = 0;
	while (current && current->token && current->token[0] == '-'
		&& current->token[1] == 'n')
	{
		i = 2;
		while (current->token[i] == 'n')
			i++;
		if (current->token[i] != '\0')
			break ;
		found = 1;
		current = current->next;
	}
	if (found)
		return (ON);
	else
		return (OFF);
}

void	b_echo(t_data *data)
{
	t_input	*current;
	int		n_flag;
	int		first;
	int		i;

	n_flag = OFF;
	first = 1;
	current = data->input->next;
	while (current && current->token && current->token[0] == '-'
		&& current->token[1] == 'n')
	{
		i = 2;
		while (current->token[i] == 'n')
			i++;
		if (current->token[i] != '\0')
			break ;
		n_flag = ON;
		current = current->next;
	}
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_OP || current->type == T_SKIP)
		{
			current = current->next;
			continue;
		}
		if (current->token != NULL)
		{
			if (!first)
				write(STDOUT_FILENO, " ", 1);
			write(STDOUT_FILENO, current->token, strlen(current->token));
			first = 0;
		}
		current = current->next;
	}
	if (n_flag == OFF)
		write(STDOUT_FILENO, "\n", 1);
	data->exit_code = 0;
	exit(0);
}
