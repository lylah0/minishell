/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/30 18:53:28 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"
/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..`
/// @param data Pointer to the shell data structure containing environment variables
/// @param arg Path to change the current working directory to
void b_cd(t_data *data, t_input *arg)
{
	t_env	*current;
	t_env	*head;
	char	*temp_pwd;
	char	*path;

	arg = data->input->next;
	if (!arg || !arg->token)
		path = getenv("HOME");
	else
		path = arg->token;
	if (!path)
	{
		fprintf(stderr, "cd: HOME not set\n");
		return;
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return;
	}
	temp_pwd = NULL;
	current = data->env;
	head = data->env;
	while (current && ft_strncmp(current->name, "PWD", 3) != 0)
		current = current->next;

	if (current && ft_strncmp(current->name, "PWD", 3) == 0)
	{
		temp_pwd = ft_strdup(current->value);
		free(current->value);
		current->value = getcwd(NULL, 0);
	}
	current = head;
	while (current && ft_strncmp(current->name, "OLDPWD", 6) != 0)
		current = current->next;

	if (current && ft_strncmp(current->name, "OLDPWD", 6) == 0)
	{
		free(current->value);
		current->value = temp_pwd;
	}
}
// [ ] gerer si pas dargument, retour racine
// [ ] cd 'src/exec'
