/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/20 21:02:59 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

int find_equal(char *s)
{
	int i = 0;

	while(s[i])
	{
		if (s[i] == '=')
			return i;
		i++;
	}
	return 0;
}

char	*extract_name(char *env_var)
{
	char	*new_name;
	int		end;

	end = find_equal(env_var);
	new_name = ft_strndup(env_var, end);
	if (!new_name)
		return NULL;
	return (new_name);
}

char	*extract_value(char *env_var)
{
	char	*new_value;
	char	*end;

	end = ft_strchr(env_var, '=');
	new_value = ft_strdup(end + 1);
	if (!new_value)
		return NULL;
	return (new_value);
}

/// @brief builtin affiche, ajoute ou maj environnement
/// @example `export` `export NAME` `export NAME=` `export NAME=value` `export NAME1=value NAME2=value`
/// @param data
void	b_export(t_data *data)
{
	t_input *arg;
	char	*new_name;
	char	*new_value;

	arg = data->input->next; // ✅ on commence à l'élément après "export"
	if (!data->env || !data->env->name)
	{
		printf("Aucune variable d'environnement\nInitialisation d'un environnement vide...\n");
		data->env         = malloc(sizeof *data->env);
		data->env->name   = ft_strdup("Head_of_environnement");
		data->env->value  = NULL;
		data->env->next   = NULL;
		return ;
	}
	if (!arg || arg->type == T_PIPE)
	{
		print_export(data);
		return ;
	}
	while (arg && arg->type != T_PIPE)
	{
		if (ft_strchr(arg->token, '=') == NULL)
		{
			if (is_valid_env_name_var_syntax(arg->token) == TRUE)
				add_env_name(data, arg->token);
			else
				data->exit_code = 1;
		}
		else
		{
			new_name = extract_name(arg->token);
			new_value = extract_value(arg->token);
			if (!new_name || !new_value)
			{
				free(new_name);
				free(new_value);
				data->exit_code = 2;
				return ;
			}
			if (is_valid_env_name_var_syntax(new_name) == TRUE
				&& is_valid_env_value_syntax(new_value) == TRUE)
			{
				if (search_env_name(data->env, new_name) == NULL)
					add_new_env_var_and_value(data, new_name, new_value);
				else
					update_env_value(data, new_name, new_value);
			}
			else
				data->exit_code = 1;
			free(new_name);
			free(new_value);
		}
		arg = arg->next;
	}
}


