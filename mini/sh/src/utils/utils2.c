/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:07:22 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 09:25:04 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_input* cat_token(t_input* token, char* value, int len)
{
	t_input* new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new_token = malloc(sizeof(t_input));
	if (!new_token)
		return (NULL);
	new_token->token = malloc(sizeof(char) * (len + 1));
	if (!new_token->token)
	{
		free(new_token);
		return (NULL);
	}
	while (token->token[i] && token->token[i] != '$')
	{
		new_token->token[j] = token->token[i];
		i++;
		j++;
	}
	while (value[k])
	{
		new_token->token[j] = value[k];
		k++;
		j++;
	}
	new_token->token[j] = '\0';
	return (new_token);
}

int	str_isdigit(char* str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char* strjoin_name_equal_value(char* name, char* value)
{
	int i = 0;
	int j = 0;
	int tot_len;
	if (value)
		tot_len = ft_strlen(name) + ft_strlen(value) + 4;
	else
		tot_len = ft_strlen(name) + 1;
	char* s = malloc(sizeof(char) * tot_len);
	if (!s)
		return NULL;
	while (name[i])
	{
		s[i] = name[i];
		i++;
	}
	if (value)
	{
		s[i++] = '=';
		s[i++] = '"';
		while (value[j])
			s[i++] = value[j++];
		s[i++] = '"';
	}
	s[i] = '\0';
	return (s);
}

void	swap_words(char** a, char** b)
{
	char* temp;
	temp = NULL;

	temp = *a;
	*a = *b;
	*b = temp;
}