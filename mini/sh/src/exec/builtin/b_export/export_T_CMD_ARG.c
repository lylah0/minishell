/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/05 21:47:47 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

/// @brief check if env var name syntax is valid
/// @param s env var name
/// @return
bool	is_valid_env_var_syntax(char *s)
{
	int		i;
	char	c;

	i = 0;
	if (!s || !*s || ft_isdigit(s[0]) || s[0] == '=')
		return (FALSE);
	while (s[i] && s[i] != '=')
	{
		c = s[i];
		if (!(ft_isalnum(c) || c == '_'))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*extract_name(char *input)
{
	char	*separator;
	char	*extracted_name;

	separator = ft_strchr(input, '=');
	if (!separator)
		return (input);
	extracted_name = ft_substr(input, 0, separator - input);
	return (extracted_name);
}

char	*extract_value(char *input)
{
	char	*separator;
	char	*extracted_value;

	separator = ft_strchr(input, '=');
	if (!separator)
		return (ft_strdup(""));
	else
		extracted_value = ft_substr(input, separator - input + 1,
				ft_strlen(input) - (separator - input + 1));
	return (extracted_value);
}

/// @brief add or maj
/// @param input
void	add_env_var(t_data *data, char *input)
{
	t_env	*current;
	char	*extracted_value;
	char	*extracted_name;
	t_env	*new_node;
	t_env	*env_last;

	current = data->env;
	(void)input;
	extracted_name = extract_name(input);
	extracted_value = extract_value(input);
	current = exist_already_in_env(data->env, extracted_name);
	if (current == NULL)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
		{
			perror("malloc");
			return ;
		}
		new_node->name = extracted_name;
		if (extracted_value[1])
			new_node->value = extracted_value;
		new_node->next = NULL;
		env_last = lle_last(data->env);
		if (env_last)
			env_last->next = new_node;
		else
			data->env = new_node;
	}
	else // mettre variable a jour
	{
		if (!extracted_value || extracted_value[0] == '\0')
			extracted_value = current->value;
		current->value = extracted_value;
	}
}

/// @brief Check if an environment variable with the given name already exists in the linked list
/// @param env Pointer to the head of the environment variable linked list
/// @param name_var Name of the environment variable to search for
/// @return Pointer to the t_env node if the variable exists, NULL otherwise
t_env	*exist_already_in_env(t_env *env, char *name_var)
{
	if (!name_var || !env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, name_var, ft_strlen(name_var)) == 0)
			return (env);
		else
			env = env->next;
	}
	return (NULL);
}
