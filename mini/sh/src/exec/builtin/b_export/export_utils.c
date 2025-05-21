/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 22:11:30 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 14:00:55 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

int	find_equal(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*extract_name(char *env_var)
{
	char	*new_name;
	int		end;

	end = find_equal(env_var);
	new_name = ft_strndup(env_var, end);
	if (!new_name)
		return (NULL);
	return (new_name);
}

char	*extract_value(char *env_var)
{
	char	*new_value;
	char	*end;

	end = ft_strchr(env_var, '=');
	new_value = ft_strdup(end + 1);
	if (!new_value)
		return (NULL);
	return (new_value);
}
