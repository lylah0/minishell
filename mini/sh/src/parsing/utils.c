/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:53:51 by lylrandr          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/16 15:03:52 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/05/16 18:07:02 by lylrandr         ###   ########.fr       */
>>>>>>> origin/main
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_char_to_result(char **result, char c)
{
	char	tmp_str[2];
	char	*tmp;
	char	*old;

	tmp_str[0] = c;
	tmp_str[1] = '\0';
	tmp = ft_strjoin(*result, tmp_str);
	old = *result;
	*result = tmp;
	free(old);
}

int	handle_special_cases(const char *src, int *i, char **result)
{
	if (src[*i] == '?')
	{
		(*i)++;
		return (1);
	}
	if (!src[*i] || (!ft_isalnum(src[*i]) && src[*i] != '_'))
	{
		append_str_to_result(result, "$");
		return (1);
	}
	return (0);
}

void	append_str_to_result(char **result, const char *str)
{
	char	*tmp;

	tmp = ft_strjoin(*result, str);
	free(*result);
	*result = tmp;
}

int	handle_normal_word(t_data *data, char *input, char **array, int *k, int i)
{
	int	len;

	len = word_len(&input[*k]);
	array[i] = malloc(sizeof(char) * (len + 256));
	if (!array[i])
		return (0);
	if_n_op(data, input, array, k, &i);
	return (1);
}

int count_tokens(const char *input)
{
	int i = 0;
	int len = 1;

	while (input[i])
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			len++;
			i = while_quotes(input, i);
			if (input[i] == '\0')
				break;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			len++;
		else if (input[i] == ' ' || input[i] == '\t')
		{
			len++;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			if (input[i] == '\0')
				break;
			i--;
		}
		i++;
	}
	return (len + 1);
}

