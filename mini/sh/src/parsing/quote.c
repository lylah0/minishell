/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:51 by lylrandr          #+#    #+#             */
/*   Updated: 2025/03/27 18:34:13 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//Appelle la fonction qui enleve les quotes et remplace par les nouveaux tokens
/*
void	remove_quotes(t_input *head)
{
	t_input	*curr;
	char	*new;

	curr = head;
	while (curr)
	{
		if (curr->type == T_SQUOTE || curr->type == T_DQUOTE)
		{
			new = handle_quoted_token(curr->token);
			if (!new)
				return ;
			free(curr->token);
			curr->token = new;
		}
		curr = curr->next;
	}
}*/

void	parse_and_expand_token(t_input *token)
{
	int		i = 0;
	char	*input;
	char	*result;
	char	*temp;

 	result = ft_calloc(1, sizeof(char));
	input = token->token;
	while (input[i])
	{
		if (input[i] == '\'')
			temp = handle_single_quote(input, &i);
		else if (input[i] == '"')
			temp = handle_double_quote(input, &i);
		else if (input[i] == '$')
			temp = handle_env_variable(input, &i);
		else
			temp = extract_plain_text(input, &i);

		char *joined = ft_strjoin(result, temp);
		free(result);
		result = joined;
		free(temp);
	}
	free(token->token);
	token->token = result;
	token->type = T_WORD;
}

char *handle_single_quote(char *str, int *i)
{
	int		start;
	int		len;

	start = ++(*i);
	len = 0;
	while (str[*i] && str[*i] != '\'')
	{
		(*i)++;
		len++;
	}
	if (str[*i] == '\'')
		(*i)++;
	return (ft_substr(str, start, len));
}

char	*handle_double_quote(char *str, int *i)
{
	int		start;
	int		len;

	start = ++(*i);
	len = 0;
	while (str[*i] && str[*i] != '"')
	{
		(*i)++;
		len++;
	}
	char *content = ft_substr(str, start, len);
	if (str[*i] == '"')
		(*i)++;
	char *expanded = expand_token_string(content);
	free(content);
	return expanded;
}

char	*handle_env_variable(char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (!str[*i] || (!ft_isalnum(str[*i]) && str[*i] != '_' && str[*i] != '?'))
		return ft_strdup("$");
	var_name = extract_var_name(str, i);
	if (!var_name)
		return ft_strdup("");
	var_value = getenv(var_name);
	free(var_name);
	if (!var_value)
		return ft_strdup("");
	return ft_strdup(var_value);
}

char *extract_plain_text(char *str, int *i)
{
	int start = *i;
	int len = 0;

	while (str[*i] && str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
	{
		(*i)++;
		len++;
	}
	return ft_substr(str, start, len);
}

/*
int	num_var(t_input *token)
{
	int	i;
	int	num;

	i = 0;
	while (token->token[i])
	{
		if (token->token[i] == '$')
			num++;
		i++;
	}
	return (num);
}
*/
