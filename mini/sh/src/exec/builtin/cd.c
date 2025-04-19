/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/19 14:31:49 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int		cd_back(t_data *data)
{
	t_env	*current_dir_env;
	char	*temp;
	char	*back_path;
	
	back_path = getenv("OLDPWD");
	if (!back_path)
	{
		ft_printf("cd: OLDPWD not set\n");
		return (1);
	}

	if (chdir(back_path) == -1)//ERROR
	{
		perror("cd");
		return 1;
	}
	else
	{	
		current_dir_env = search_env_name(data->env, "OLDPWD");
		temp = current_dir_env->value;
		ft_printf("%s\n", back_path);
		current_dir_env->value = ft_strdup(getenv("PWD"));
		current_dir_env = search_env_name(data->env, "PWD");
		free(current_dir_env->value);
		current_dir_env->value = ft_strdup(back_path);
		free(temp);


		// temp = current_dir_env->value;//je stock le nom de dir actuel pour quil devienne apres lancien dir

		// free (current_dir_env->value);
		// current_dir_env->value = back_path;

		// current_dir_env = search_env_name(data->env, "OLDPWD");
		// free (current_dir_env->value);
		// current_dir_env->value = temp;
	}
	return 0;
}


/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..` 
/// @param data Pointer to the shell data structure containing environment variables
/// @param arg Path to change the current working directory to
void	b_cd(t_data *data)
{
	t_env	*current_dir_env;
	char	*home_path;

	if (data->input->type == T_CMD)
	{
		home_path = getenv("HOME");
		if (!home_path)
		{
			ft_printf("cd: HOME not set\n");
			return;
		}
		if (chdir(home_path) == -1)
		{
			perror("cd");
			return;
		}
		current_dir_env = search_env_name(data->env, "OLDPWD");
		if (current_dir_env)
		{
			free(current_dir_env->value);
			current_dir_env->value = ft_strdup(getenv("PWD"));
		}
		current_dir_env = search_env_name(data->env, "PWD");
		if (current_dir_env)
		{
			free(current_dir_env->value);
			current_dir_env->value = ft_strdup(home_path);
		}
	}
	else
	{
		if (ft_strncmp(data->input->next->token, "-", 1) == 0)
			cd_back(data);
		// if (data->input->token == "..")
		// if (data->input->token == ) path + /path
	}
	
}



/*
	Change the current working directory to directory. 
	If directory is not supplied, 
		the value of the HOME shell variable is used. 
	If the shell variable CDPATH exists, it is used as a search path: 
		each directory name in CDPATH is searched for directory, 
		with alternative directory names in CDPATH separated by a colon(‘:’). 
	If directory begins with a slash, CDPATH is not used.

	If the directory change is successful, cd sets 
		the value of the PWD environment variable to the new directory name, and sets 
		the OLDPWD environment variable to the value of the current working directory before the change.
		The return status is 
			zero if the directory is successfully changed, 
			non-zero otherwise.

	`chdir(path)` retourne 0 si succès, -1 si erreur (ex : chemin inexistant, pas des 
	droits, etc.). On doit alors gérer les erreurs : par ex, si le dossier n’existe pas, afficher 
	`minishell: cd: <path>: No such file or directory`. Si c’est un fichier et pas un dossier : `Not 
	a directory`.  
*/