/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:09:08 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/16 18:09:01 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**second_parsing(char **array)
{
	char	**result;
	int		len;

	if (!array)
		return (NULL);
	len = count_second_parsing_len(array);
	result = malloc_second_parsing(len);
	if (!result)
		return (NULL);
	return (fill_second_tab(array, result));
}

void	handle_operator(char **tab_token, char **array, int *index, int i)
{
	tab_token[*index] = ft_strdup(array[i]);
	(*index)++;
}

int	handle_non_operator(char **tab_token, char *array, int *index)
{
	tab_token[*index] = ft_strdup(array);
	if (!tab_token[*index])
		return (0);
	(*index)++;
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

char	**parse_input(t_data *data, char *input)
{
	char	**first_parse;
	char	**final_parse;

	if (!input)
		return (NULL);
	if (is_open_quotes(input))
	{
		ft_putendl_fd("minishell: syntax error: unclosed quote", 2);
		free(input);
		return (NULL);
	}
	first_parse = first_parsing(data, input);
	if (!first_parse)
		return (NULL);
	final_parse = second_parsing(first_parse);
	free_tab(first_parse);
	if (!final_parse)
		return (NULL);
	return (final_parse);
}
