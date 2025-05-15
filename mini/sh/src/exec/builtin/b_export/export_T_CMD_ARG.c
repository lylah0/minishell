/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/14 17:18:12 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

bool is_valid_env_var_syntax(char *s)
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
				ft_printf_stderr("minishell: export: '%s': not a valid identifier\n", s);
				return (FALSE);
			}
		}
		return (TRUE);
	}
	ft_printf_stderr("minishell: export: `%s': not a valid identifier\n", s);
	return (FALSE);
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
