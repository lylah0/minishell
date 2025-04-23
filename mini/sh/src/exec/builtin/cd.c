/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/22 16:48:56 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

// (t_env *env_oldpwd, t_env *env_pwd, char *new_pwd, char *old_pwd)

t_env	*update_env(t_env *env, char *env_to_update, char *new_value)
{
	t_env	*current;
	
	current = search_env_name(env, env_to_update);// je pourrais ne pas trouver l'env_var
	if (current == NULL)
		return NULL;
	free (current->value);
	current->value = ft_strdup(new_value);
	// free(new_value);
	return (current);// return env_to_update
}

void cd_home(t_env *env)
{
	char *old_pwd;
	char *new_pwd;

	old_pwd = getcwd(NULL, 0);
	update_env(env, "OLDPWD", old_pwd);
	new_pwd = getenv("HOME");
	
	if (getenv("HOME") == NULL)
		perror("minishell: cd");
	update_env(env, "PWD", new_pwd);
}
// [ ] HOME non defini message derreur / cd: HOME not set
// [ ] voir utilisation correcte de perror


void cd_return(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = strdup((search_env_name(data->env, "OLDPWD"))->value);
	if (new_pwd == NULL)
	{
		perror("getenv");
		data->exit_status = 1;
		return ;
	}

	old_pwd = strdup((search_env_name(data->env, "PWD"))->value);
	if (old_pwd == NULL)
	{
		perror("oldpwd");
		data->exit_status = 1;
		return ;
	}

	if (chdir(new_pwd) == -1)
	{
		perror("cd");
		free(new_pwd);// ?
		data->exit_status = 1;
		return ;
	}
	update_env(data->env, "OLDPWD", old_pwd);
	update_env(data->env, "PWD", new_pwd);
	free(new_pwd);
	free(old_pwd);
	data->exit_status = 0;
}
// lylah [ ] commande invalide ajouter message dans terminal


void	cd_path(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	// old_pwd = getcwd(NULL, 0);
	old_pwd = (search_env_name(data->env, "PWD"))->value;
	if (old_pwd == NULL)
	{
		perror("PWD");
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
	update_env(data->env, "OLDPWD", old_pwd);

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		// perror("getcwd");
		data->exit_status = 1;
		return ;
	}
	update_env(data->env, "PWD", new_pwd);
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


// [ ] verifier la validite du dossier ouvert
// [ ] trop dargumetnts message erreur
// [ ] cas ou je supprime PWD, cd, segv --> bash: cd: OLDPWD not set
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
