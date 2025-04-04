/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:49:28 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/04 13:31:29 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

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
		ft_putstr_fd("export \"", 1);
		ft_putstr_fd(data->copy_env[i], 1);
		ft_putendl_fd("\"",1);
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
