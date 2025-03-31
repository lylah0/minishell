/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:33:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/31 13:45:41 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// typedef struct s_env
// {
// 	char			*name;
// 	char			*value;
// 	struct s_env	*next;
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

bool is_valid_env_var_syntax(char *s_env)
{
	int		i;
	char	c;

	i = 0;
	if (s_env[i] == '_' || ft_isalpha(s_env[i]) == TRUE)
	{
		i++;
		while (s_env[i])
		{
			c = s_env[i];
			if (c == '_' || ft_isalnum(c) == TRUE)
				i++;
			else
				return (FALSE);
		}
		return (TRUE);
	}
	// ft_putendl_fd("bash: export: '		[ ] a completer
	// 	X
	// 	': not a valid identifier", 1);
	return (FALSE);
}

void	init_env(t_data *data, char **envp)
{
	data->env = create_env_linked_list(envp);
	//print_env_linked_list(data);
	create_env_copy_array(data);
	sort_words(data->copy_env, get_array_length(data->copy_env));
	//print_copy_env(data);
	free_env_linked_list(data);
//	b_export(data, (t_input *)data->input);
}

void	b_export(t_data *data, t_input *input)
{
	if (input->type == T_CMD)
	{
		printf("hello");
		// create_env_copy_array(data);
		// sort_words(data->copy_env, get_array_length(data->copy_env));
		// print_copy_env(data);
		// free_env_linked_list(data);
	}
	else
		return;
	(void)data;
}
