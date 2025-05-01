/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:59:39 by monoguei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/01 15:09:53 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/04/18 17:22:23 by monoguei         ###   ########.fr       */
=======
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:59:39 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/01 14:27:54 by monoguei         ###   ########.fr       */
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
>>>>>>> eb617a4c514e795db0ef1fe9f6c22ce25ebbf2de
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

void    b_echo(t_input *input)
{
	int flag_newline = OFF;

	input = input->next;
	while (input && input->token && (input->type == T_ARG || input->type == T_WORD) && (input->type == T_ARG || input->type == T_WORD))
	{
		if (is_n_option(input->token) == ON)
		{
			flag_newline = ON;
			input = input->next;
			continue;
		}
		printf("%s", input->token);
		if (input->next)
		{
			printf(" ");
			input = input->next;
		}
		else
			break ;
	}
	if (flag_newline == OFF)
		printf("\n");
}