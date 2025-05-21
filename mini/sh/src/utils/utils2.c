/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:07:22 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 17:00:31 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_until_dollar(char *dst, const char *src, int *i, int *j)
{
	while (src[*i] && src[*i] != '$')
	{
		dst[*j] = src[*i];
		(*i)++;
		(*j)++;
	}
}

void	copy_value(char *dst, const char *value, int *j)
{
	int	k = 0;
	while (value[k])
	{
		dst[*j] = value[k];
		k++;
		(*j)++;
	}
}

t_input	*cat_token(t_input *token, char *value, int len)
{
	t_input	*new_token;
	int		i = 0;
	int		j = 0;

	new_token = malloc(sizeof(t_input));
	if (!new_token)
		return (NULL);
	new_token->token = malloc(sizeof(char) * (len + 1));
	if (!new_token->token)
	{
		free(new_token);
		return (NULL);
	}
	copy_until_dollar(new_token->token, token->token, &i, &j);
	copy_value(new_token->token, value, &j);
	new_token->token[j] = '\0';
	return (new_token);
}

