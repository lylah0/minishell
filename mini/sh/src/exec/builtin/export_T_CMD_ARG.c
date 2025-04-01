/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/01 21:59:32 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief check if env var name syntax is valid
/// @param s env var name 
/// @return 
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
			if (c == '_' || ft_isalnum(c) == TRUE)
				i++;
			else
				return (FALSE);
		}
		return (TRUE);
	}
	ft_putendl_fd("bash: export: '", 1);//		[ ] a completer
	ft_printf("%s", s);
	ft_putendl_fd("': not a valid identifier", 1);
	return (FALSE);
}

/// @brief add or maj
/// @param input 
void	add_env_var(char *input)
{
	// int		i = 0;
	t_env	*current = NULL;
	t_env	*head = NULL;
	t_env	*temp = NULL;
	char	*separator;	
	(void)temp;
	(void)head;
	
	if (!current)
	{
		current = malloc(sizeof(t_env));
		if (!current)
		{
			free(current);
			return ;
		}
	}
	separator = ft_strchr(input, '=');
	if (separator)
	{
		current->name = ft_substr(input, 0, separator - input);
		current->value = ft_strdup(separator + 1);
	}
	else
	{
		current->name = ft_strdup(input);
		current->value = NULL;
	}
	current->next = NULL;
	if (!current->name || (separator && !current->value))
	{
		free(current->name);
		return ;
	}
}

t_env *exist_already_in_env(t_env *env, t_env *name_var)
{
	if (!name_var || !env)
		return (NULL);
	while (env)
	{
		// if (ft_strncmp(env->name, (const char *)name_var, ft_strlen(name_var) == TRUE))
		// 	return (env); [ ] condition a refaire
		// else
		// 	env = env->next;
	}
	return (NULL);
}

