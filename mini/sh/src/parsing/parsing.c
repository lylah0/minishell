/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:39:34 by lylrandr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/16 15:05:06 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/05/16 18:08:07 by lylrandr         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**first_parsing(t_data *data, char *input)
{
	char	**array;
	int		len;

	len = count_tokens(input);
	array = malloc(sizeof(char *) * (len + 1));
	if (!array)
	{
		perror("first_parsing");
		return (NULL);
	}
	array[len] = NULL;
	return (fill_tab(data, input, array));
}

int	word_len(char *input)
{
	int		i;
	int		in_quote;
	char	quote_char;

	i = 0;
	in_quote = 0;
	quote_char = 0;
	while (input[i])
	{
		if (quotes(input, &i, &in_quote, &quote_char))
			continue ;
		if (!in_quote && (input[i] == ' ' || input[i] == '|' || input[i] == '<'
				|| input[i] == '>'))
			break ;
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

void	if_n_op(t_data *data, char *input, char **array, int *k, int *i)
{
	int		j;
	int		in_quote;
	char	quote_char;

	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (input[*k] && !(input[*k] == ' ' && !in_quote) && !(input[*k] == '|'
			&& !in_quote) && !(input[*k] == '<' && !in_quote)
		&& !(input[*k] == '>' && !in_quote))
	{
		if (input[*k] == '$')
			expand_env_var_into_array(data, input, &array[*i], k, &j);
		else if (quotes(input, k, &in_quote, &quote_char))
			continue ;
		else
		{
			array[*i][j] = input[*k];
			j++;
			(*k)++;
		}
	}
	array[*i][j] = '\0';
}

char	**fill_tab(t_data *data, char *input, char **array)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	array[i] = NULL;
	while (input[k])
	{
		while (input[k] == ' ')
			k++;
		if (!input[k])
			break ;
		if (input[k] == '\'' || input[k] == '"')
			if_quotes(input, array, &k, &i);
		else if (input[k] == '|' || input[k] == '<' || input[k] == '>')
			if_operator(input, array, &k, i);
		else if (!handle_normal_word(data, input, array, &k, i))
			return (NULL);
		i++;
	}
	array[i] = NULL;
	return (array);
}
