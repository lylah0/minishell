/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 22:42:44 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*update_env_value(t_env *env, char *env_to_update, char *new_value)
{
	t_env	*current;

	if (!env_to_update || !new_value)
		return (NULL);
	current = search_env_name(env, env_to_update);
	if (!current)
	{
		ft_printf_stderr("cd: %s not set\n", env_to_update);
		exit_code = 1;
		return (NULL);
	}
	free (current->value);
	current->value = ft_strdup(new_value);
	if (!current->value)
		return NULL;
	return (current);
}

void	cd_home(t_data *data)
{
	char *home_value;
	char *new_oldpwd_value;

	home_value = ft_strdup(search_env_value(data->env, "HOME"));
	new_oldpwd_value = ft_strdup(search_env_value(data->env, "PWD"));
	if (chdir(home_value) == -1)
	{
		perror("cd -");
		free (new_oldpwd_value);
		free (home_value);
		exit_code = 1;
		return ;
	}
	update_env_value(data->env, "OLDPWD", new_oldpwd_value);
	update_env_value(data->env, "PWD", home_value);
	free(new_oldpwd_value);
	free(home_value);
}
void	cd_return(t_data *data)
{
	char	*new_pwd_value;
	char	*new_oldpwd_value;

	new_oldpwd_value = getcwd(NULL, 0);
	new_pwd_value = ft_strdup(search_env_value(data->env, "OLDPWD"));
	if (chdir(new_oldpwd_value) == -1)
	{
		perror("cd -");
		free (new_oldpwd_value);
		free (new_pwd_value);
		exit_code = 1;
		return ;
	}
	update_env_value(data->env, "OLDPWD", new_oldpwd_value);
	update_env_value(data->env, "PWD", new_pwd_value);
	free(new_oldpwd_value);
	free(new_pwd_value);
}
void	cd_path(t_data *data)
{
	char	*new_pwd_value;
	char	*new_oldpwd_value;

	new_oldpwd_value = getcwd(NULL, 0);
	if (chdir(data->input->next->token) == -1)
	{
		ft_printf_stderr("bash: cd: %s: ", data->input->next->token);
		perror("");
		free(new_oldpwd_value);
		exit_code = 1;
		return ;
	}
	new_pwd_value = getcwd(NULL, 0);
	update_env_value(data->env, "OLDPWD", new_oldpwd_value);
	update_env_value(data->env, "PWD", new_pwd_value);
	free(new_oldpwd_value);
	free(new_pwd_value);
}


/// @brief built-in change directory `cd <path>`, `cd`, `cd -`, `cd..`
/// @param data Pointer to the shell data structure containing environment variables
/// @param arg Path to change the current working directory to
void b_cd(t_data *data)
{
	t_input		*arg;

	arg = data->input->next;
	if (!arg)
		cd_home(data);
	else if (arg && ft_strncmp_end(arg->token, "-", 1) == 0)
	{
		if (ft_strlen(arg->token)>1)
			ft_printf_stderr("option not needed for minishell\n"); //seulement cd - est géré, pas d'options -*
		else
		{
			cd_return(data);
			b_pwd(data);
		}
	}
	else if (arg && !arg->next)
		cd_path(data);
	else
	{
		ft_printf_stderr("bash: cd: too many arguments\n");
		exit_code = 1;
	}
}
