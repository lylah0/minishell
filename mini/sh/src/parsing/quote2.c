/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:13:05 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/15 22:05:40 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_quoted_token(char *quoted_str)
{
	int		len;
	int		j;
	int		i;
	char	*result;

	len = ft_strlen(quoted_str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (quoted_str[i])
	{
		if (quoted_str[i] == quoted_str[0])
		{
			i++;
			continue ;
		}
		result[j++] = quoted_str[i++];
	}
	result[j] = '\0';
	return (result);
}

char	**malloc_second_parsing(int len)
{
	char	**tab_token;

	tab_token = ft_calloc(len + 1, sizeof(char *));
	if (!tab_token)
	{
		perror("malloc_second_parsing");
		return (NULL);
	}
	return (tab_token);
}

void	if_quotes(char *input, char **array, int *k, int *i)
{
	char	quote;
	int		start;
	int		len;

	quote = input[*k];
	start = *k;
	(*k)++;
	while (input[*k] && input[*k] != quote)
		(*k)++;
	if (input[*k] == quote)
		(*k)++;
	else
	{
		printf("missing one quote\n");
		return ;
	}
	while (input[*k] && input[*k] != ' ' && input[*k] != '|' && input[*k] != '<'
		&& input[*k] != '>' && input[*k] != ';' && input[*k] != '&'
		&& input[*k] != '(' && input[*k] != ')')
		(*k)++;
	len = *k - start;
	copy_substring(input, &array[*i], start, len);
}

int	while_quotes(const char *input, int i)
{
	if (input[i - 1] != ' ' || input[i - 1] != '\t')
		i++;
	if (input[i] == '\'')
	{
		i++;
		while (input[i] && input[i] != '\'')
			i++;
	}
	else if (input[i] == '"')
	{
		i++;
		while (input[i] && input[i] != '"')
			i++;
	}
	while (input[i + 1] != ' ' && input[i + 1] != '|' && input[i + 1] != '<'
		&& input[i + 1] != '>' && input[i + 1])
		i++;
	return (i);
}

int	is_open_quotes(char *input)
{
	int	i;
	int	in_dquote;
	int	in_squote;

	i = 0;
	in_dquote = 0;
	in_squote = 0;
	while (input[i])
	{
		if (input[i] == '"' && !in_squote)
			in_dquote = !in_dquote;
		else if (input[i] == '\'' && !in_dquote)
			in_squote = !in_squote;
		i++;
	}
	if (in_dquote || in_squote)
		return (1);
	return (0);
}
