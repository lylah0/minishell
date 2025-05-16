/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:01:38 by lylrandr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/16 14:56:48 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/05/16 18:05:19 by lylrandr         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	quotes(char *input, int *k, int *in_quote, char *quote_char)
{
	if (!*in_quote && (input[*k] == '\'' || input[*k] == '"'))
	{
		*in_quote = 1;
		*quote_char = input[*k];
		(*k)++;
		return (1);
	}
	if (*in_quote && input[*k] == *quote_char)
	{
		*in_quote = 0;
		(*k)++;
		return (1);
	}
	return (0);
}

int	copy_substring(char *input, char **array_ptr, int start, int len)
{
	int	j;

	*array_ptr = malloc(sizeof(char) * (len + 1));
	if (!*array_ptr)
		return (0);
	j = 0;
	while (j < len)
	{
		(*array_ptr)[j] = input[start + j];
		j++;
	}
	(*array_ptr)[j] = '\0';
	return (1);
}

int	count_second_parsing_len(char **array)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	i = 0;
	while (array[i])
	{
		if (array[i][0] == '\0' || array[i][0] == '\'' || array[i][0] == '"')
		{
			len++;
			i++;
			continue ;
		}
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == ' ')
				len++;
			j++;
		}
		len++;
		i++;
	}
	return (len);
}

int	append_to_result(char **result, char *temp)
{
	char	*joined;

	joined = ft_strjoin(*result, temp);
	free(*result);
	*result = joined;
	free(temp);
	if (!*result)
		return (0);
	return (1);
}

char	*expand_token_part(char *input, int *i, t_data *data)
{
	if (input[*i] == '\'')
		return (handle_single_quote(input, i));
	if (input[*i] == '"')
		return (handle_double_quote(input, i, data));
	if (input[*i] == '$')
		return (handle_env_variable(data, input, i));
	return (extract_plain_text(input, i));
}
