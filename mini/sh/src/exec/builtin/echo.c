/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 09:12:01 by monoguei         ###   ########.fr       */
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

void	b_echo(t_data *data)
// void	b_echo(t_input *cmd)
{
	t_input *current = data->input->next;
	// t_input *current =/ cmd->next;
	int n_flag = OFF;

	// Gérer les -n au début
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

	// Afficher les arguments restants
	while (current && current->type != T_PIPE)
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

/*
TESTS
	minishell> echo hello        world           !
	hello world !
	minishell> echo            hello
	minishell> echo "              " pisselit
				   pisselit
	hello
	minishell> echo

	minishell> echo 1
	1
	minishell> echo 1 3 33
	1 3 33
	minishell> echo $
	$
	minishell> echo $?
	0
	minishell> echo $?$
	0$
[ ]	minishell> echo $7USER		--> USER

	minishell> echo $USER
	moni
	minishell> echo $USER$PWD
	moni/home/moni/Desktop/CODE/mini_moni_restart (1)/minishell_ly_mo-214359c22ccd6bac686e576e8b6cc662fdacc6e7/mini/sh

	minishell> echo $U

[ ] minishell> echo $U ee		--> ee (pas d'espace au debut)
	 ee
	minishell> echo   eee
	eee
	minishell> echo hello
	hello
-n	minishell> echo -n hello
	hellominishell> echo -nnnn hello
	hellominishell> echo -nnnnx hello
	-nnnnx hello
	minishell> echo hello -n
	hello -n
	minishell> echo -n -n
	minishell> echo -n tulipe -n
	tulipe -nminishell>
	minishell> echo -nhello
	-nhello
	minishell> echo ---------n
	---------n
	minishell> echo -n -nnn pamplemousse -n
	pamplemousse -nminishell>



[ ]	minishell> echo \n hello
	\n hello					--> n hello
*/
