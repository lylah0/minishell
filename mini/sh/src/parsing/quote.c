/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:58:51 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/08 15:08:59 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_and_expand_token(t_input *token, t_data *data)
{
	int		i = 0;
	char	*input = token->token;
	char	*result = ft_calloc(1, sizeof(char));
	char	*temp;
	char	*joined;

	while (input[i])
	{
		if (input[i] == '\'')
			temp = handle_single_quote(input, &i);
		else if (input[i] == '"')
			temp = handle_double_quote(input, &i, data);
		else if (input[i] == '$')
			temp = handle_env_variable(input, &i);
		else
			temp = extract_plain_text(input, &i);
		if (!temp)
			break;
		joined = ft_strjoin(result, temp);
		free(result);
		result = joined;
		free(temp);
	}
	if (!result)
		result = ft_strdup("");
	free(token->token);
	token->token = result;
	if (token->token[0] == '\0')
		token->type = T_SKIP;
	else
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

char	*handle_double_quote(char *str, int *i, t_data *data)
{
	char	*content;
	char	*expanded;
	int		start;
	int		len;

	start = ++(*i);
	len = 0;
	printf("ici\n");
	printf("str: %s, start: %d\n", str, start);
	while (str[*i] && str[*i] != '"')
	{
		(*i)++;
		len++;
	}
	content = ft_substr(str, start, len);
	if (str[*i] == '"')
		(*i)++;
	expanded = expand_token_string(content, data);
	free(content);
	return (expanded);
}

char	*handle_env_variable(char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	if (str[*i + 1] == '?')
	{
		*i += 2;
		return ft_itoa(exit_code);
	}
	(*i)++;
	if (!str[*i] || (!ft_isalnum(str[*i]) && str[*i] != '_'))
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
