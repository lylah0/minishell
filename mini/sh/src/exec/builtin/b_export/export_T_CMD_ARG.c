/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD_ARG.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:48:31 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/04 16:11:39 by monoguei         ###   ########.fr       */
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
				printf("export_T_CMD_ARG.c > is_valid_env_var_syntaxe1\t");
				ft_putstr_fd("bash: export: '", 1);
				ft_printf("%s", s);
				ft_putendl_fd("': not a valid identifier", 1);
				return (FALSE);
			}
		}
		printf("export_T_CMD_ARG.c > is_valid_env_var_syntaxe2\tSUCCESS is a valid SYNTAX env_var(%s) :)\n", s);
		return (TRUE);
	}
	printf("export_T_CMD_ARG.c > is_valid_env_var_syntaxe3\t");
	ft_putstr_fd("bash: export: '", 1);
	ft_printf("%s", s);
	ft_putendl_fd("': not a valid identifier", 1);
	return (FALSE);
}
t_env	*go_end_of_linked_list(t_env *env)
{
	if (!env)
		return (NULL);
	while (env->next)
	{
		env = env->next;
	}
	return (env);
}

char	*extract_name(char *input)
{
	char	*separator;
	char	*extracted_name;

	if (input)
	{
		separator = ft_strchr(input, '=');
		if (separator)// maj value
		{
			extracted_name = ft_substr(input, 0, separator - input);
			return (extracted_name);
		}
		else
			return (input);
	}
	return (NULL);
}
// printf("export_T_CMD_ARG.c > add_env_var :\tSUCCESS name(%s) extracted from imput(%s) :)\n", extracted_name, input);
// printf("export_T_CMD_ARG.c > add_env_var :\tcurrent->name(%s)\n", current->name);

char	*extract_value(char *input)
{
	char	*separator;
	char 	*extracted_value;

	if(input)
	{
		separator = ft_strchr(input, '=');
		if (separator)// maj value
		{
			extracted_value = ft_substr(input, separator - input + 1, ft_strlen(input) - (separator - input + 1));
			return (extracted_value);
		}
	}
	return (NULL);
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
	printf("export_T_CMD_ARG.c > add_env_var :\t BEFORE extract value(%s)\n", extracted_value);
	extracted_value = extract_value(input);
	printf("export_T_CMD_ARG.c > add_env_var :\t AFTER extract value(%s)\n", extracted_value);
	
	current = exist_already_in_env(data->env, extracted_name);// current == NULL si input na pas ete trouve dans env
	printf("export_T_CMD_ARG.c > add_env_var :\tUpdated env var with name(%s) to BEFORE value(%s)\n", extracted_name, extracted_value);
	if (current == NULL) // variable does not exist
	{
		t_env *new_node = malloc(sizeof(t_env));
		if (!new_node)
		{
			perror("malloc");
			return;
		}
		new_node->name = extracted_name;
		new_node->value = extracted_value;
		new_node->next = NULL;
		lle_add_back(&data->env, new_node);
		printf("export_T_CMD_ARG.c > add_env_var :\tAdded new env var with name(%s) and value(%s)\n", extracted_name, extracted_value);
	}
	else
	{
		if (ft_strchr(input, '=') != NULL)
		{
			free(current->value);

			current->value = extracted_value;
			printf("export_T_CMD_ARG.c > add_env_var :\tUpdated env var with name(%s) to new value(%s)\n", extracted_name, extracted_value);
		}
		else
			return ;
		free(extracted_name);
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
		{
			printf("export_T_CMD_ARG.c > exist_already_in_env :\tenv_var with name %s found befor %s\n", env->name, env->next->name);
			return (env);
		}
		else
			env = env->next;
	}
	printf("export_T_CMD_ARG.c > exist_already_in_env :\tno match env_name_linked_list / env_name_input_token \n");
	
	return (NULL);
}
