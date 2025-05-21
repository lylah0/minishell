/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:53:51 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 13:26:17 by lylrandr         ###   ########.fr       */
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

int	handle_normal_word(t_data *data, char *input, int *k, int i)
{
	int	len;

	len = word_len(&input[*k]);
	data->array[i] = malloc(sizeof(char) * (len + 256));
	if (!data->array[i])
		return (0);
	if_n_op(data, input, k, &i);
	return (1);
}

int	count_tokens(const char *input)
{
	int	i;
	int	len;

	i = 0;
	len = 1;
	while (input[i])
	{
		if (!handle_token_logic(input, &i, &len))
			break ;
		if (!input[i])
			break ;
		i++;
	}
	return (len + 1);
}
