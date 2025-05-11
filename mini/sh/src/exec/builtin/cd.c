/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 20:22:09 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/11 20:53:54 by monoguei         ###   ########.fr       */
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

/*
TESTScd
OK	cd .
OK	cd ./
OK	cd ./././.
OK	cd ././././
OK	cd ..
OK	cd ../
OK	cd ../..
OK	cd ../.
OK	cd .././././.
OK	cd srcs
OK	cd srcs objs		bash: cd: too many arguments
OK	cd 'srcs'
OK	cd "srcs"
OK	cd /etc				bash: cd: /mini: No such file or directory
OK	cd sr
[OK]	cd Makefile			cd: Makefile: No such file or directory
OK	cd /
OK	cd '/'
[ ]	cd //				pwd = / --> pwd = //
OK	cd ////////
[ ]	cd /minishell		?
OK	cd _
OK	cd -
[ ]	cd --				like cd_return --> bash: cd: --: invalid option
							cd: usage: cd [-L|[-P [-e]] [-@]] [dir]
[ ]	cd ---				like cd_return --> bash: cd: --: invalid option (exactement pareil !!)
							cd: usage: cd [-L|[-P [-e]] [-@]] [dir]

OK	cd $HOME
OK	cd $HOME $HOME
OK	cd $HOME/42_works
a tester	[ ]	1 unset HOME
				2 cd $HOME
			[ ]	1 unset HOME
				2 export HOME=
				3 cd
			[ ]	1 unset HOME
				2 export HOME
				3 cd
$> cd minishell Docs crashtest.c
"$>    cd / | echo $?
$> pwd"
$> cd ~
$> cd ~/
"$> cd ~/ | echo $?
$> pwd"
$> cd *
$> cd *
$> cd *
"$> mkdir a
$> mkdir a/b
$> cd a/b
$> rm -r ../../a
$> cd .."
"$> mkdir a
$> mkdir a/b
$> cd a/b
$> rm -r ../../a
$> pwd"
"$> mkdir a
$> mkdir a/b
$> cd a/b
$> rm -r ../../a
$> echo $PWD
$> echo $OLDPWD"
"$> mkdir a
$> mkdir a/b
$> cd a/b
$> rm -r ../../a
$> cd
$> echo $PWD
$> echo $OLDPWD"
"$> mkdir a
$> cd a
$> rm -r ../a
$> echo $PWD
$> echo $OLDPWD"*/
