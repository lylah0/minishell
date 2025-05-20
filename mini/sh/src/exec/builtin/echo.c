/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/20 19:49:01 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define OFF 0
#define ON 1

int	n_option(t_input *input)
{
	t_input	*current;
	int		found;

	current = input->next;
	found = 0;
	while (current && current->type != T_PIPE)
	{
		if (current->type == T_OP)
		{
			if (current->next)
				current = current->next;
			current = current->next;
			continue ;
		}
		if (current->type == T_SKIP)
		{
			current = current->next;
			continue ;
		}
		current = current->next;
	}
	if (found)
		return (ON);
	else
		return (OFF);
}

void	b_echo(t_data *data, t_input *current)
{
	t_input	*curr;
	int		n_flag;
	int		first;
	int		i;

	n_flag = OFF;
	first = 1;
	curr = current->next;
	while (curr && curr->token && curr->token[0] == '-'
		&& curr->token[1] == 'n')
	{
		i = 2;
		while (curr->token[i] == 'n')
			i++;
		if (curr->token[i] != '\0')
			break ;
		n_flag = ON;
		curr = curr->next;
	}
	while (curr && curr->type != T_PIPE)
	{
		if (curr->type == T_OP)
		{
			if (curr->next)
				curr = curr->next;
			curr = curr->next;
			continue ;
		}
		if (curr->type == T_SKIP)
		{
			curr = curr->next;
			continue ;
		}
		if (curr->token != NULL)
		{
			if (!first)
				write(STDOUT_FILENO, " ", 1);
			if (curr->token != NULL)
				write(STDOUT_FILENO, curr->token, ft_strlen(curr->token));
			first = 0;
		}
		curr = curr->next;
	}
	if (n_flag == OFF)
		write(STDOUT_FILENO, "\n", 1);
	data->exit_code = 0;
	exit(0);
}
