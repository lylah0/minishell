/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:39:34 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/11 19:41:42 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**first_parsing(char *input)
{
	int		i;
	int		len;
	char	**array;

	i = 0;
	len = 1;
	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			len++;
			i = while_quotes(input, i);
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			len++;
		else if (input[i] == ' ' || input[i] == '\t')
		{
			len++;
			while (ft_iswhitespace(input[i]))
				i++;
			i -= 1;
		}
		i++;
	}
	len++;
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
	{
		perror("first_parsing");
		return (NULL);
	}
	array[len] = NULL;
	return (fill_tab(input, array));
}

int	word_len(char *input)
{
	int		i;
	char	quote;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '\'' || input[i] == '"')
	{
		if (input[i - 1] != ' ' || input[i - 1] != '\t')
			i++;
		quote = input[i];
		i++;
		while (input[i] && input[i] != quote)
			i++;
		if (input[i] == quote)
			i++;
		return (i);
	}
	else
	{
		while (input[i] && input[i] != '|' && input[i] != '>' && input[i] != '<'
			&& input[i] != ' ')
			i++;
		return (i);
	}
}

void	if_operator(char *input, char **array, int *k, int i)
{
	int	j;
	int	len;

	j = 0;
	len = 0;
	while (input[*k + len] == '|' || input[*k + len] == '<' || input[*k
		+ len] == '>')
		len++;
	array[i] = malloc(sizeof(char) * (len + 1));
	if (!array[i])
		return ;
	while (input[*k] == '|' || input[*k] == '<' || input[*k] == '>')
	{
		array[i][j] = input[*k];
		j++;
		(*k)++;
	}
	array[i][j] = '\0';
}

void	if_n_op(char *input, char **array, int *k, int *i)
{
	int		j = 0;
	char	quote;

	while (input[*k] && input[*k] != ' ' && input[*k] != '|' &&
		input[*k] != '<' && input[*k] != '>')
	{
		if (input[*k] == '\'' || input[*k] == '"')
		{
			quote = input[*k];
			(*k)++;
			while (input[*k] && input[*k] != quote)
				array[*i][j++] = input[(*k)++];
			if (input[*k] == quote)
				(*k)++;
		}
		else
		{
			array[*i][j++] = input[(*k)++];
		}
	}
	array[*i][j] = '\0';
}


char	**fill_tab(char *input, char **array)
{
	int	i;
	int	k;
	int	len;

	i = 0;
	k = 0;
	array[i] = NULL;
	while (input[k])
	{
		while (input[k] == ' ')
			k++;
		len = word_len(&input[k]);
		if (input[k] == '\'' || input[k] == '"')
			if_quotes(input, array, &k, &i);
		else if (input[k] == '|' || input[k] == '<' || input[k] == '>')
			if_operator(input, array, &k, i);
		else
		{
			array[i] = malloc(sizeof(char) * (len + 1));
			if (!array[i])
				return (NULL);
			if_n_op(input, array, &k, &i);
		}
		i++;
	}
	i = 0;
	return (array);
}
