/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/01 16:25:52 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*update_env(t_env *env, char *env_to_update, char *new_value)
{
	t_env	*current;

	current = search_env_name(env, env_to_update);// [ ] (+) verification : je pourrais ne pas trouver l'env_var
	if (current == NULL)
	{
		perror("bash: cd: env_var not found");
		return NULL;
	}
	free (current->value);
	current->value = ft_strdup(new_value);
	if (!current->value)
		return NULL;
	return (current);
}

void cd_home(t_env *env)
{
	char *old_pwd;
	char *new_pwd;

	old_pwd = getcwd(NULL, 0);
	update_env(env, "OLDPWD", old_pwd);
	new_pwd = getenv("HOME");

	if (new_pwd && search_env_value_safe(env, "HOME") == NULL)// getenv(HOME) ??
	{
		perror("minishell: cd HOME not set");
		return ;
	}
	update_env(env, "PWD", new_pwd);
}
// [x] HOME non defini message derreur / cd: HOME not set
// [x] voir utilisation correcte de perror


void cd_return(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = strdup((search_env_name(data->env, "OLDPWD"))->value);
	// if (new_pwd == NULL) // doublon avec verif dans cd main
	// {
	// 	perror("OLDPWD");
	// 	data->exit_status = 1;
	// 	return ;
	// }

	old_pwd = strdup((search_env_name(data->env, "PWD"))->value);
	if (old_pwd == NULL)
	{
		perror("PWD");
		data->exit_status = 1;
		return ;
	}

	if (chdir(new_pwd) == -1)
	{
		perror("cd -");
		free(new_pwd);
		data->exit_status = 1;
		return ;
	}
	update_env(data->env, "OLDPWD", old_pwd);
	update_env(data->env, "PWD", new_pwd);
	free(new_pwd);
	free(old_pwd);
	data->exit_status = 0;
}
// lylah [x] commande invalide ajouter message dans terminal


void	cd_path(t_data *data)
{
	char	*old_pwd = getcwd(NULL, 0);
	char	*new_pwd;

	// old_pwd = getcwd(NULL, 0);
	// old_pwd = (search_env_name(data->env, "PWD"))->value;
	if (old_pwd == NULL)
	{
		perror("getcwd");
		// perror("PWD");
		data->exit_status = 1;
		return ;
	}
	if (chdir(data->input->next->token) == -1)
	{
		perror("cd <path>");
		free(old_pwd);
		data->exit_status = 1;
		return ;
	}
	update_env(data->env, "OLDPWD", old_pwd);
	free(old_pwd);//

	new_pwd = getcwd(NULL, 0);
	if (new_pwd == NULL)
	{
		perror("getcwd");
		data->exit_status = 1;
		return ;
	}
	update_env(data->env, "PWD", new_pwd);
	free(new_pwd);//
	data->exit_status = 0;
}
#define OK 0
#define ERR 1
int check_opening_dir(char *directory)
{
	if (opendir(directory) == NULL)
	{
		perror("opendir");
		return (ERR);
	}
	return (OK);
}

/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..`
/// @param data Pointer to the shell data structure containing environment variables
/// @param arg Path to change the current working directory to
void b_cd(t_data *data)
{
	struct stat	st;
	char		*path;
	char		*oldpwd;

	if (data->input->type == T_CMD)
	{
		cd_home(data->env);
		// b_pwd(data);
	}
	else if (ft_strncmp(data->input->next->token, "-", 1) == 0 && !data->input->next->next)
	{
		oldpwd = ft_strdup((char *)search_env_name(data->env, "OLDPWD"));
		if (oldpwd == NULL)
		{
			perror("OLDPWD");
			return ;
		}
		cd_return(data);
		b_pwd(data);// need to stay to be like bash --posix
		free (oldpwd);
	}
	else if (data->input->next && data->input->next->next)
		perror("cd: too many arguments");
	else
	{
		path = data->input->next->token;
		// if (stat(path, &st) == 0 && S_ISDIR(st.st_mode) && check_opening_dir(path) == OK)
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode) && !data->input->next->next)
		{
			cd_path(data);
			// b_pwd(data);
		}
		else
		{
			perror("cd: path invalid");
			data->exit_status = 1;
		}
	}
}
