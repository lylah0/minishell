/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/01 16:35:33 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

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
			if (c == '_' || ft_isalnum(c) || c == '=')
				i++;
			else
			{
				ft_putstr_fd("bash: export: '", 1);
				ft_printf("%s", s);
				ft_putendl_fd("': not a valid identifier", 1);
				return (FALSE);
			}
		}
		return (TRUE);
	}
	ft_putstr_fd("bash: export: '", 1);
	ft_printf("%s", s);
	ft_putendl_fd("': not a valid identifier", 1);
	return (FALSE);
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
		extracted_value = ft_substr(input, separator - input + 1, ft_strlen(input) - (separator - input + 1));
	return (extracted_value);
}

/// @brief add or maj
/// @param input 
void	add_env_var(t_data *data, char *input)
{
	t_env	*current = data->env;
	char 	*extracted_value;
	char 	*extracted_name;
	(void)input;
	extracted_name = extract_name(input);
	extracted_value = extract_value(input);
	current = exist_already_in_env(data->env, extracted_name);// current == NULL si input na pas ete trouve dans env
	if (current == NULL) // variable does not exist
	{
		t_env *new_node = malloc(sizeof(t_env));
		if (!new_node)
		{
			// perror("malloc");
			return;
		}
		new_node->name = extracted_name;
		if (extracted_value[1])
			new_node->value = extracted_value;
		new_node->next = NULL;

		t_env *env_last = lle_last(data->env);
		if (env_last)
			env_last->next = new_node;
		else
			data->env = new_node;
	}
	else //mettre variable a jour
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
t_env *exist_already_in_env(t_env *env, char *name_var)
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