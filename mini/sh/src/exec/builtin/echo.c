/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/12 19:32:55 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define OFF 0
#define ON 1

int n_option(t_input *input)
{
	t_input *current = input->next;
	int found = 0;

	while (current && current->token && current->token[0] == '-' && current->token[1] == 'n')
	{
		int i = 2;
		while (current->token[i] == 'n')
			i++;
		if (current->token[i] != '\0')
			break;
		found = 1;
		current = current->next;
	}
	if (found)
		return ON;
	else
		return OFF;
}

void	b_echo(t_input *cmd)
{
	t_input *current;
	int n_flag = OFF;

	current = cmd->next;
	while (current && current->token && current->token[0] == '-' && current->token[1] == 'n')
	{
		int i = 2;
		while (current->token[i] == 'n')
			i++;
		if (current->token[i] != '\0')
			break;
		n_flag = ON;
		current = current->next;
	}
	while (current && (current->type != T_PIPE && current->type != T_OP)) // ajout de t_op pour ne pas print ">/<"
	{
		ft_printf("%s", current->token);
		if (current->next && current->next->type != T_PIPE)
			ft_printf(" ");
		current = current->next;
	}
	if (n_flag == OFF)
		ft_printf("\n");
	exit_code = 0;
}
