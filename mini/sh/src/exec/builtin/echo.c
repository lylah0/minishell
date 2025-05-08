/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/08 14:56:20 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define OFF 0
#define ON 1

int is_n_option(const char *token)
{
	if (ft_strncmp(token, "-n", 2) == 0)
	{
		int i = 2;
		while (token[i] && token[i] == 'n')
			i++;
		if (token[i] == '\0')
			return ON;
	}
	return OFF;
}

void b_echo(t_input *input)
{
	int flag_newline = OFF;

	input = input->next;
	while (input && input->token)
	{
		if (input->type == T_SKIP)
		{
			input = input->next;
			continue;
		}
		if (input->type == T_OP && input->next)
		{
			input = input->next->next;
			continue;
		}
		if (is_n_option(input->token) == ON)
		{
			flag_newline = ON;
			input = input->next;
			continue;
		}
		ft_printf("%s", input->token);
		if (input->next && (input->next->type == T_WORD || input->next->type == T_ARG))
			ft_printf(" ");
		input = input->next;
	}
	if (flag_newline == OFF)
		ft_printf("\n");
}

