/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 22:41:00 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

bool is_valid_env_name_var_syntax(char *s)
{
	int		i;
	char	c;

	i = 0;
	if (s[i] == '_' || ft_isalpha(s[i]) == TRUE)
	{
		i++;
		while (s[i])
		{
			c = s[i];
			if (c == '_' || ft_isalnum(c) || c == '=')
				i++;
			else
			{
				ft_printf_stderr("bash: export: env_name '%s': not a valid identifier\n", s);
				return (FALSE);
			}
		}
		return (TRUE);
	}
	ft_printf_stderr("bash: export: env_name '%s': not a valid identifier\n", s);
	return (FALSE);
}

bool is_valid_env_value_syntax(char *s)
{
	int i = 0;
	char c = s[i];
	int len_s = ft_strlen(s);
	
	// if (s[0] == '"' && s[len_s] == '"')
	// {
	// 	while (ft_isascii(c))
	// 		i++;
	// 	if (i == len_s)
	// 		return TRUE;
	// }
	while (s[i])
	{
		if (ft_isalnum(c) || c == '_'|| c == '=' || c == '-' || c == '.' || c == '\\')
			i++;
	}
	if (i != len_s)
	{
		ft_printf_stderr("bash: export: env_value: '%s': not a valid identifier\n", s);
		return FALSE;
	}
	return TRUE;
}

void	add_env_name(t_data *data, char *env_name)
{
	t_env	*new_node;

	if (!data || !env_name)
		return;
	if (search_env_name(data->env, env_name) == NULL)// si cette var n'existe pas
	{
		new_node = lle_new(env_name, NULL);
		lle_add_back(&data->env, new_node);
	}
}
void	add_new_env_var_and_value(t_data *data, char *env_name, char *env_value)
{
	t_env	*new_node;

	if (!data || !env_name || !env_value)
		return;
	if (search_env_name(data->env, env_name) == NULL)// si cette var n'existe pas
	{
		new_node = lle_new(env_name, env_value);
		lle_add_back(&data->env, new_node);
	}
}