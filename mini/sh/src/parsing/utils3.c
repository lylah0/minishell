/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:29:52 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 16:44:00 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_env_var_into_array(t_data *data, char *input, char **array_ptr,
		int *k, int *j)
{
	char	*expanded;
	int		l;

	expanded = handle_env_variable(data, input, k);
	if (expanded && expanded[0] != '\0')
	{
		l = 0;
		while (expanded[l])
		{
			(*array_ptr)[*j] = expanded[l];
			(*j)++;
			l++;
		}
	}
	free(expanded);
}

int	handle_token_logic(const char *input, int *i, int *len)
{
	if (input[*i] == '"' || input[*i] == '\'')
	{
		(*len)++;
		*i = while_quotes(input, *i);
	}
	else if (input[*i] == '|' || input[*i] == '<' || input[*i] == '>')
		(*len)++;
	else if (input[*i] == ' ' || input[*i] == '\t')
	{
		(*len)++;
		while (input[*i] == ' ' || input[*i] == '\t')
			(*i)++;
		if (!input[*i])
			return (0);
		(*i)--;
	}
	return (1);
}

int	ft_striswhitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (FALSE);
		i++;
	}
	return (TRUE);
}
