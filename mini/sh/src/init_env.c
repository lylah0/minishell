/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:33:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/01 18:50:17 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// typedef struct s
// {
// 	char			*name;
// 	char			*value;
// 	struct s	*next;
// }					t_env;

void	free_env_linked_list(t_data *data)
{
	t_env *temp = NULL;

	while (data->env)
	{
		temp = data->env->next;
		free(data->env->name);
		free(data->env->value);
		free(data->env);
		data->env = temp;
	}
}

void	print_env_linked_list(t_data *data)
{
	while (data->env)
	{
		printf("%s=", data->env->name);// pourquoi ca ne simprime pas si linked list imprimer aussi ? verifier coherence printf write
		printf("%s\n", data->env->value);// pourquoi ca ne simprime pas si linked list imprimer aussi ? verifier coherence printf write
		data->env = data->env->next;
	}
}

t_env	*create_env_linked_list(char **envp)
{
	int		i = 0;
	t_env	*current = NULL;
	t_env	*head = NULL;
	t_env	*temp = NULL;
	char	*separator;

	while (envp[i])
	{
		current = malloc(sizeof(t_env));
		if (!current)
		{
			free(current);
			return (0);
		}
		separator = ft_strchr(envp[i], '=');
		if (separator)
		{
			current->name = ft_substr(envp[i], 0, separator - envp[i]);
			current->value = ft_strdup(separator + 1);
		}
		else
		{
			current->name = ft_strdup(envp[i]);
			current->value = NULL;
		}
		current->next = NULL;
		if (!current->name || (separator && !current->value))
		{
			free(current->name);
			return (0);
		}
		if (!head)
			head = current;
		else
			temp->next = current;
		temp = current;
		i++;
	}
	return (head);
}
/// @brief swap words for sort NAME of environnement `export`
/// @param a
/// @param b
void	swap_words(char **a, char **b)
{
	char *temp;
	temp = NULL;

	temp = *a;
	*a = *b;
	*b = temp;
}

// ret 1 = swap nec
// ret 0 = PAS de swap
int	compare_words(char *w1, char *w2)
{
	int i = 0;

	while (w1[i] && w2[i])
	{
		if (w1[i] < w2[i])
			return 0;//
		if (w1[i] > w2[i])
			return 1;// b > a SWAP
		if  (w1[i] == w2[i])
			i++;
	}
	if (w1[i])
		return 1;
	else
		return 0;
}

void	sort_words(char	**words, int len)
{
	int	i = 0;
	int	j = 1;

	while(i < len && j < len)
	{
		if (compare_words(words[i], words[j]) == 1)
			swap_words(&words[i], &words[j]);
		else
			j++;
		if (j == len)
		{
			i++;
			j = i + 1;
		}
	}
}

void 	print_copy_env(t_data *data)
{
	int i;

	i = 0;
	while (data->copy_env[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putendl_fd(data->copy_env[i], 1);
		i++;
	}
}

void	create_env_copy_array(t_data *data)
{
	t_env	*current;
	char	*name;
	char	*value;
	int		i;
	int		env_count;

	i = 0;
	env_count = 0;
	current = data->env;

	while (current)
	{
		env_count++;
		current = current->next;
	}
	data->copy_env = malloc((env_count + 1) * sizeof(char *));// [malloc a liberer !][_]
	if (!data->copy_env)
		return ;

	current = data->env;

	while (current)
	{
		name = ft_strdup_equal(current->name);
		// name = ft_strdup(current->name);
		value = ft_strdup(current->value);
		if (!name || !value)
		{
			free(name);
			free(value);
			return ;
		}
		data->copy_env[i] = ft_strjoin(name, value);
		free(name);
		free(value);
		i++;
		current = current->next;
	}
	data->copy_env[i] = NULL;
}
int get_array_length(char **array)
{
	int len = 0;
	while (array[len])
		len++;
	return len;
}

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

// /// @brief add or maj
// /// @param input 
// /// @return 
// t_env	*add_env_var(char *input)
// {
// 	int		i = 0;
// 	t_env	*current = NULL;
// 	t_env	*head = NULL;
// 	t_env	*temp = NULL;
// 	char	*separator;	
	
// 	if (!current)
// 	{
// 		current = malloc(sizeof(t_env));
// 		if (!current)
// 		{
// 			free(current);
// 			return (NULL);
// 		}
// 	}
// 	separator = ft_strchr(input, '=');
// 	if (separator)
// 	{
// 		current->name = ft_substr(input, 0, separator - input);
// 		current->value = ft_strdup(separator + 1);
// 	}
// 	else
// 	{
// 		current->name = ft_strdup(input);
// 		current->value = NULL;
// 	}
// 	current->next = NULL;
// 	if (!current->name || (separator && !current->value))
// 	{
// 		free(current->name);
// 		return (NULL);
// 	}
// }


// t_env *exist_already_in_env(t_env *env, t_env *name_var)
// {
// 	if (!name_var || !env)
// 		return (NULL);
// 	while (env)
// 	{
// 		if (ft_strncmp(env->name, name_var, ft_strlen(name_var) == TRUE))
// 			return (t_env);
// 		else
// 			env = env->next;
// 	}
// 	return (NULL);
// }

// void	maj_var_env(t_env *name)
// {
// 	add_env_var(name);
// }

// /// @brief built-in `export` `export VAR=value` `export VAR` `export VAR+=value`
// /// @param data 
// void	b_export(t_data *data)
// {
// 	(void)data;
// 	// t_env	*current;
// 	// if (data->input->type == T_CMD)
// 	if ((*data->input).type == T_CMD)
// 	{
// 		// create_env_copy_array(data);
// 		// sort_words(data->copy_env, get_array_length(data->copy_env));
// 		// print_copy_env(data);
// 		printf("\n\t\t\t\t\tT_CMD\n");
// 		// free_env_linked_list(data);
// 	}
// 	if ((*data->input).type == T_CMD_ARG)
// 	{	
// 		// if (is_valid_env_var_syntax(data->input->next->token) == TRUE)
// 		// {
// 		// 	if (current = exist_already_in_env(data->env, data->input->next->token))
// 		// 		maj_var_env(current);
// 		// 	else
// 		// 		data->env = add_env_var(data->input->next->token);
// 		// }
// 		printf("\n\t\t\t\t\tT_CMD_ARG\n");
// 	}
// 	return;
// }



/// @brief 
/// @param data 
/// @param envp 
void	init_env(t_data *data, char **envp)
{
	data->env = create_env_linked_list(envp);
	//print_env_linked_list(data);
	// create_env_copy_array(data);
	// sort_words(data->copy_env, get_array_length(data->copy_env));
	//print_copy_env(data);
	// free_env_linked_list(data);
}
