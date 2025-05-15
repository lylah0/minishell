/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:39:34 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/15 14:30:33 by lylrandr         ###   ########.fr       */
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
	int		i = 0;
	int		in_quote = 0;
	char	quote_char = 0;

	while (input[i])
	{
		if (!in_quote && (input[i] == '\'' || input[i] == '"'))
		{
			in_quote = 1;
			quote_char = input[i];
			i++;
			continue;
		}
		if (in_quote && input[i] == quote_char)
		{
			in_quote = 0;
			i++;
			continue;
		}
		if (!in_quote && (input[i] == ' ' || input[i] == '|' || input[i] == '<' || input[i] == '>'))
			break;
		i++;
	}
	return (i);
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
	int		in_quote = 0;
	char	quote_char = 0;

	while (input[*k] && !(input[*k] == ' ' && !in_quote) &&
			!(input[*k] == '|' && !in_quote) &&
			!(input[*k] == '<' && !in_quote) &&
			!(input[*k] == '>' && !in_quote))
	{
		if (!in_quote && (input[*k] == '\'' || input[*k] == '"'))
		{
			in_quote = 1;
			quote_char = input[*k];
			(*k)++;
			continue;
		}
		if (in_quote && input[*k] == quote_char)
		{
			in_quote = 0;
			(*k)++;
			continue;
		}
		array[*i][j++] = input[(*k)++];
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
		if (!input[k])
			break;
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
	array[i] = NULL;
	return (array);
}
