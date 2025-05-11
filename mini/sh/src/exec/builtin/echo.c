/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:49:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/11 19:10:06 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

#define OFF 0
#define ON 1

int n_option(t_input *input)
{
	int	i;

	if (ft_strncmp(input->next->token, "-n", 2) == TRUE)
	{
		i = 1;
		while (input->token[i] == 'n')
			i++;
		if (input->token[i]) // cas "-nnnnnnnnnnnx" (il y a encore qqch apres "-n" qui nest pas un "n")
			return OFF;
		else // cas "-n" ou "-nnnnnnnnnnnnnnnnn"
			return ON;
	}
	else
		return OFF;
}

void	b_echo(t_data *data)
{
	t_input *current;

	current = data->input->next;
	while (current && current->type != T_PIPE)
	{
		ft_printf("%s", current->token);
		if (current->next)
		{
			if (current->next->type != T_WORD || current)// $USE moi "moi" " moi"
				ft_printf(" ");
			current = current->next;
		}
		else
			break ;
	}
	if (n_option(data->input) == OFF)
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
