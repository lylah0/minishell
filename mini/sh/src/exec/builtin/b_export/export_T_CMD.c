/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_T_CMD.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:49:28 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/20 22:11:38 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

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
}
