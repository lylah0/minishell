/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:11:06 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/23 11:08:13 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	tester_cd(char **envp)
{
	char	**input = malloc(sizeof(char *) * 3);
	t_data	*data = malloc(sizeof(t_data));
	input[0] = "cd";
	input[1] = "src";
	input[2] = NULL;

	init_env(data, envp);
	b_pwd();
	b_cd(data, input[1]);
	b_pwd();
	free(input);
}

// int		tester_echo(void)
// {
// 	char	**input = malloc(sizeof(char *) * 4);
// 	input[0] = "Elise";
// 	input[1] = "a";
// 	input[2] = "raison";
// 	input[3] = NULL;
// 	b_echo(input);
// 	free(input);
// 	return (0);
// }

void	tester_env(char **envp)
{
	t_data	*data = malloc(sizeof(t_data));
	init_env(data, envp);
	// b_env(data);
	// b_export(data);	
}

int		tester_pwd(void)
{
	b_pwd();
	return (0);
}

// void	tester_export(void)
// {
// 	t_data	*data = malloc(sizeof(t_data));
// 	b_export(data);
// }

void	tester_cd(char **envp);
// int		tester_echo(void);
void	tester_env(char **envp);
int		tester_pwd(void);