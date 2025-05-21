/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:01:05 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 17:02:58 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	str_isdigit(char *str)
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

void	copy_name(char *dst, const char *name, int *i)
{
	while (name[*i])
	{
		dst[*i] = name[*i];
		(*i)++;
	}
}

void	copy_value_with_quotes(char *dst, const char *value, int *i)
{
	int	j;
    
    j = 0;
	dst[(*i)++] = '=';
	dst[(*i)++] = '"';
	while (value[j])
		dst[(*i)++] = value[j++];
	dst[(*i)++] = '"';
}

char	*strjoin_name_equal_value(char *name, char *value)
{
	int		i = 0;
	int		tot_len;
	char	*s;

	if (value)
		tot_len = ft_strlen(name) + ft_strlen(value) + 4;
	else
		tot_len = ft_strlen(name) + 1;
	s = malloc(sizeof(char) * tot_len);
	if (!s)
		return (NULL);
	copy_name(s, name, &i);
	if (value)
		copy_value_with_quotes(s, value, &i);
	s[i] = '\0';
	return (s);
}

void	swap_words(char **a, char **b)
{
	char *temp;

	temp = NULL;
	temp = *a;
	*a = *b;
	*b = temp;
}
