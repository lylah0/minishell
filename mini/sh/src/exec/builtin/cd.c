/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/03 12:04:15 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*update_env(t_env *env, char *env_to_update, char *new_value)
{
	t_env	*current;

	current = search_env_name(env, env_to_update);
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

	if (new_pwd && search_env_value_safe(env, "HOME") == NULL)
	{
		ft_putstr_fd("minishell: cd HOME not set", 2);
		return ;
	}
	update_env(env, "PWD", new_pwd);
}

void cd_return(t_data *data)
{
	char	*old_pwd;
	char	*new_pwd;

	new_pwd = strdup((search_env_name(data->env, "OLDPWD"))->value);

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
	}
	else if (ft_strncmp(data->input->next->token, "-", 1) == 0 && !data->input->next->next)
	{
		oldpwd = ft_strdup((char *)search_env_name(data->env, "OLDPWD"));
		if (oldpwd == NULL)
			return ;
		cd_return(data);
		b_pwd(data);// need to stay to be like bash --posix
		free (oldpwd);
	}
	else if (data->input->next && data->input->next->next)
		ft_putstr_fd(" too many arguments\n", 2);
	else
	{
		path = data->input->next->token;
		if (stat(path, &st) == 0 && S_ISDIR(st.st_mode) && !data->input->next->next)
			cd_path(data);
		else
		{
			ft_putstr_fd(" No such a file or directory\n", 2);
			data->exit_status = 1;
		}
	}
}
