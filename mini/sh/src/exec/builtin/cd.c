/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/21 20:20:50 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..` 
/// @param data 
/// @param arg <path>
void b_cd(t_data *data, char *arg)
{
    t_env	*current;
	t_env	*head;
	char	*temp_pwd;

	temp_pwd = NULL;
		
	current = data->env;
	head = data->env;

	while (current && ft_strncmp(current->name, "PWD", 3) != 0)
		current = current->next;
	if (ft_strncmp(current->name, "PWD", 3) == 0)
	{
		temp_pwd = ft_strdup(current->value);
		if (chdir(arg) == 0)
		{
			free(current->value);
			current->value = getcwd(NULL, 0);
		}
		else
		perror("cd");
	}

	current = head;
	
	while (current && ft_strncmp(current->name, "OLDPWD", 6) != 0)
		current = current->next;
	if (ft_strncmp(current->name, "OLDPWD", 6) == 0)
		current->value = (char *)temp_pwd;
}

// [ ] gerer si pas dargument, retour racine
// [ ] cd 'src/exec'