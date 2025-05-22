/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:29:52 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/22 09:54:27 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	copy_expanded(char *dest, const char *src, int *j)
{
	int	l;

	l = 0;
	while (src[l])
		dest[(*j)++] = src[l++];
}

void	expand_env_var_into_array(t_data *data, char *input, char **array_ptr,
			int *k_j)
{
	char	*expanded;

	expanded = handle_env_variable(data, input, &k_j[0]);
	if (expanded && expanded[0] != '\0')
		copy_expanded(*array_ptr, expanded, &k_j[1]);
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
