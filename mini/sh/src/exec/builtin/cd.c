/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/21 16:38:53 by monoguei         ###   ########.fr       */
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
	char *home = getenv("HOME");
	chdir(home);
	current = search_env_name(env, "PWD");
	new_pwd = getenv("HOME");
	if (new_pwd == NULL)
		perror("minishell: cd: HOME not define");
	free (current->value);
	current->value = ft_strdup(new_pwd);
}

void cd_return(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = getenv("OLDPWD");
	if (new_pwd == NULL)
	{
		perror("getenv");
		data->exit_status = 1;
		return ;
	}
	old_pwd = getcwd(NULL, 0);
	if(old_pwd == NULL)
	{
		perror("getcwd");
		data->exit_status = 1;
		return ;
	}
	if (chdir(old_pwd) == -1)
	{
		perror("cd");
		free(old_pwd);
		data->exit_status = 1;
		return ;
	}
	t_env *current = search_env_name(data->env, "OLDPWD");
	free(current->value);
	current->value = old_pwd;

	current = search_env_name(data->env, "PWD");
	free(current->value);
	current->value = new_pwd;
	data->exit_status = 0;
}



void	cd_path(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if(old_pwd == NULL)
	{
		perror("getcwd");
		data->exit_status = 1;
		return ;
	}
	if (chdir(data->input->next->token) == -1)
	{
		perror("cd");
		free(old_pwd);
		data->exit_status = 1;
		return ;
	}
	t_env *current = search_env_name(data->env, "OLDPWD");
	free(current->value);
	current->value = old_pwd;
	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd");
		data->exit_status = 1;
		return ;
	}
	current = search_env_name(data->env, "PWD");
	free(current->value);
	current->value = new_pwd;
	data->exit_status = 0;
}



/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..`
/// @param data Pointer to the shell data structure containing environment variables
/// @param arg Path to change the current working directory to
void b_cd(t_data *data)
{
	struct stat	st;
	char		*path;

	if (data->input->type == T_CMD)
	{
		cd_home(data->env);
		b_pwd(data);
	}
	else if (ft_strncmp(data->input->next->token, "-", 1) == 0)
	{	
		cd_return(data);
		b_pwd(data);// need to stay to be like bash --posix
	}
	else
	{
		path = data->input->next->token;
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
		{
			cd_path(data);
			b_pwd(data);
		}
		else
		{
			printf("cd: %s: Not a directory\n", path);
			data->exit_status = 1;
		}
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

// void cd_absolute_path(t_env *env, char *absolute_path)
// {
// 	t_env *current;
// 	char *pwd_value;
// 	char *new_pwd;
	
// 	new_pwd = NULL;
// 	pwd_value = NULL;
// 	current = search_env_name(env, "OLDPWD");
// 	new_pwd = getenv("OLDPWD");
// 	free (current->value);
// 	current->value = ft_strdup(pwd_value);
// 	new_pwd = ft_strjoin(new_pwd, absolute_path);
	
// 	if (chdir(new_pwd) == -1)
// 		perror("minishell: cd: relative path not found");

// 	pwd_value = getenv("PWD");
// 	current = search_env_name(env, "PWD");
// 	free (current->value);
// 	current->value = ft_strdup(new_pwd);
// }

// void cd_relative_path(t_env *env, char *relative_path)
// {
// 	t_env *current;
// 	char *pwd_value;
// 	char *new_pwd;

// 	new_pwd = NULL;
// 	pwd_value = NULL;

// 	current = search_env_name(env, "OLDPWD");
// 	new_pwd = getenv("OLDPWD");
// 	free (current->value);
// 	current->value = ft_strdup(pwd_value);
// 	new_pwd = ft_strjoin(new_pwd, relative_path);

// 	if (chdir(relative_path) == -1)
// 		perror("minishell: cd: relative path not found");
	
// 	pwd_value = getenv("PWD");
// 	current = search_env_name(env, "PWD");
// 	free (current->value);
// 	current->value = ft_strdup(new_pwd);	
// }