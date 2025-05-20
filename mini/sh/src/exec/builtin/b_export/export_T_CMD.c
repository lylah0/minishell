/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:49:28 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/20 11:35:07 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

char	*strjoin_name_equal_value(char *name, char *value)
{
	int i = 0;
	int j = 0;
	int tot_len;
	if (value)
		tot_len = ft_strlen(name) + ft_strlen(value) + 4;// = , \0 , " , "
	else
		tot_len = ft_strlen(name) + 1;
	char *s = malloc(sizeof(char) * tot_len);
	if (!s)
		return NULL;
	while (name[i])
	{
		s[i] = name[i];
		i++;
	}
	if (value)
	{
		s[i++] = '=';
		s[i++] = '"';
		while (value[j])
			s[i++] = value[j++];
		s[i++] = '"';
		}
	s[i] = '\0';

	return (s);
}

void lle_to_array(t_data *data)
{
	char	**copy_env;
	t_env	*current;
	int		index_array;

	(void)copy_env;
	index_array = 0;
	current = data->env;
	data->copy_env = malloc(sizeof(char *) * (lle_size(current) + 1));
	if (!data->copy_env)
		return ;
	while (current)
	{
		data->copy_env[index_array] = strjoin_name_equal_value(current->name, current->value);
		index_array++;
		current = current->next;
	}
	data->copy_env[index_array] = NULL;
}

void	swap_words(char **a, char **b)
{
	char *temp;
	temp = NULL;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	compare_words(char *w1, char *w2)
{
	int i = 0;

	while (w1[i] && w2[i])
	{
		if (w1[i] < w2[i])
			return 0;
		if (w1[i] > w2[i])
			return 1;
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

void	print_env_array(t_data *data)
{
	int	i;

	i = 0;
	while (i < lle_size(data->env))
	{

		printf("export %s\n", data->copy_env[i]);
		i++;
	}
}

void	free_array(char **array)
{
	int i;

	i = 0;
	if (!array)
		return;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void print_export(t_data *data)
{
	lle_to_array(data);
	sort_words(data->copy_env, lle_size(data->env));
	print_env_array(data);
	free_array(data->copy_env);
}
