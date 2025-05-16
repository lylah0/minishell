/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 22:39:49 by monoguei         ###   ########.fr       */
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

	arg = data->input;
	if (!arg->next || arg->next->type == T_PIPE)
		print_export(data);
	else
	{
		while (arg->next)
		{
			// if (arg->next->type == T_SKIP)
			// {
			// 	arg->next = arg->next->next;
			// 	continue ;
			// }
			printf("new_value = (%s)\n", new_value);
			if (ft_strchr(arg->next->token, '=') == NULL)// pas de '='
				{
					if (is_valid_env_name_var_syntax(new_name) == TRUE)
						add_env_name(data, arg->next->token);
				}
			else if (is_valid_env_name_var_syntax(arg->next->token) == TRUE && is_valid_env_value_syntax(new_value) == TRUE)
			{
				new_value = extract_value(arg->next->token);
				new_name = extract_name(arg->next->token);
				if (search_env_name(data->env, new_name) == NULL) // pas trouve, new value
					add_new_env_var_and_value(data, new_name, new_value);
				else // existe deja
					update_env_value(data->env, new_name, new_value);
			}
			arg->next = arg->next->next;
		}
	}
}