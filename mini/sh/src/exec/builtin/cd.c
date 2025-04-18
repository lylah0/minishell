/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/18 20:09:50 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..` 
/// @param data Pointer to the shell data structure containing environment variables
/// @param arg Path to change the current working directory to
void	b_cd(t_data **data, t_input *input)
{
	char *home_path = getenv("HOME");
	printf("home : %s\n", home_path);
	chdir(home_path);
	t_env	**pwd_env;
	(void)input;
	
	pwd_env = search_env_name((*data)->env, "PWD");
	(*pwd_env)->value = home_path;

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