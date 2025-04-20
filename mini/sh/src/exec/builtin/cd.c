/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/20 22:58:29 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void cd_home(t_env *env)
{
	t_env *current;
	char *pwd_value;
	char *new_pwd;

	current = search_env_name(env, "OLDPWD");
	pwd_value = getenv("PWD");
	free (current->value);
	current->value = ft_strdup(pwd_value);
	chdir("HOME");
	current = search_env_name(env, "PWD");
	new_pwd = getenv("HOME");
	free (current->value);
	current->value = ft_strdup(new_pwd);
}

void cd_return(t_env *env)
{
	t_env *current;
	char *new_oldpwd;
	char *new_pwd;

	current = search_env_name(env, "OLDPWD");
	new_pwd = getenv("OLDPWD");

	free (current->value);
	current->value = ft_strdup(new_pwd);
	chdir("HOME");
	current = search_env_name(env, "PWD");
	new_oldpwd = getenv("PWD");
	free (current->value);
	current->value = ft_strdup(new_oldpwd);
}

void cd_path(t_env *env, char *destination)
{
	t_env *current;
	char *pwd_value;
	char *new_pwd;

	current = search_env_name(env, "OLDPWD");
	pwd_value = getenv("PWD");
	free (current->value);
	current->value = ft_strdup(pwd_value);
	new_pwd = ft_strjoin(pwd_value, "/");
	new_pwd = ft_strjoin(new_pwd, destination);
	chdir(new_pwd);
	current = search_env_name(env, "PWD");
	free (current->value);
	current->value = ft_strdup(new_pwd);
}



/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..`
/// @param data Pointer to the shell data structure containing environment variables
/// @param arg Path to change the current working directory to
void b_cd(t_data *data)
{
	if (data->input->type == T_CMD)
	{
		cd_home(data->env);
		b_pwd(data);
	}
	else if (ft_strncmp(data->input->next->token, "-", 1) == 0)
	{	
		cd_return(data->env);
		b_pwd(data);
	}
	else if (data->input->next->token[0] == '/') // Absolute path
	{
		cd_path(data->env, data->input->next->token);
		b_pwd(data);
	}
	else
		printf("else\n");
	// else if (data->input->next->token[0] == '.' && data->input->next->token[1] == '/') // Relative path
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