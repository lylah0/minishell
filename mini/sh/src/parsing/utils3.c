/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:29:52 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/22 13:29:45 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_env_var_into_array(t_data *data, char *input, char **array_ptr,
		int *k_j)
{
	char	*expanded;
	int		l;

	expanded = handle_env_variable(data, input, &k_j[0]);
	if (expanded && expanded[0] != '\0')
	{
		l = 0;
		while (expanded[l])
		{
			(*array_ptr)[k_j[1]] = expanded[l];
			k_j[1]++;
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

void	print_token_list(t_input *head)
{
	t_input	*curr;
	int		i;

	curr = head;
	i = 0;
	printf("\n Vérification des tokens après expansion :\n");
	while (curr)
	{
		printf("Token[%d]: %s,(Type: %d)\n", i, curr->token, curr->type);
		curr = curr->next;
		i++;
	}
	printf("\n");
}

void	copy_single_char(char *input, char **array, int *k_j, int i)
{
	array[i][k_j[1]] = input[k_j[0]];
	k_j[1]++;
	k_j[0]++;
}
