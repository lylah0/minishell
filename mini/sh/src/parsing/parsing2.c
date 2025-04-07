/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid Date        by              +#+  #+#    #+#             */
/*   Updated: 2025/04/07 16:10:27 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

char	**second_parsing(char **array)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (array[i])
	{
		j = 0;
		if (array[i][0] == '\'' || array[i][0] == '"')
		{
			len++;
			i++;
			continue ;
		}
		while (array[i][j])
		{
			if (array[i][j] == ' ')
				len++;
			j++;
		}
		i++;
		len++;
	}
	return (fill_second_tab(array, malloc_second_parsing(len)));
}

void	handle_operator(char **tab_token, char **array, int *index, int i)
{
	tab_token[*index] = ft_strdup(array[i]);
	(*index)++;
}

int	handle_non_operator(char **tab_token, char *array, int *index)
{
	char	**split_tab;
	int		j;

	split_tab = ft_split(array, ' ');
	if (!split_tab)
		return (0);
	j = 0;
	while (split_tab[j])
	{
		tab_token[*index] = ft_strdup(split_tab[j]);
		(*index)++;
		j++;
	}
	j = 0;
	while (split_tab[j])
	{
		free(split_tab[j]);
		j++;
	}
	free(split_tab);
	return (1);
}

char	**fill_second_tab(char **array, char **tab_token)
{
	int	i;
	int	index;

	i = 0;
	index = 0;
	while (array[i])
	{
		if (array[i][0] == '\'' || array[i][0] == '"')
			handle_operator(tab_token, array, &index, i);
		else if (array[i][0] == '|' || array[i][0] == '<' || array[i][0] == '>')
			handle_operator(tab_token, array, &index, i);
		else
		{
			if (!handle_non_operator(tab_token, array[i], &index))
				return (NULL);
		}
		i++;
	}
	tab_token[index] = NULL;
	return (tab_token);
}

char	**parse_input(char *input)
{
	char	**first_parse;
	char	**final_parse;

	if (is_open_quotes(input))
	{
		printf("missing one quote\n");
		exit(0);
	}
	first_parse = first_parsing(input);
	if (!first_parse)
		return (NULL);
	final_parse = second_parsing(first_parse);
	if (!final_parse)
		return (NULL);
	return (final_parse);
}
