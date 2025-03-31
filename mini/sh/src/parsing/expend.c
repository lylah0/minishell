/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:51:39 by lylrandr          #+#    #+#             */
/*   Updated: 2025/03/27 18:23:23 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	replace_token(t_input *token, char *value)
{
	int		new_len;
	t_input	*new_token;

	new_len = ft_strlen(value);
	if (!token->token)
		return;
	new_token = cat_token(token, value, new_len);
	if (!new_token)
		return;
	token->token = new_token->token;
	free(new_token);
}

char	*extract_var_name(const char *str, int *i)
{
	int len = 0;
	char *name;

	if (str[*i] == '?')
	{
		(*i)++;
		return ft_strdup("?");
	}
	while (ft_isalnum(str[*i + len]) || str[*i + len] == '_')
		len++;
	name = ft_substr(str, *i, len);
	*i += len;
	return (name);
}

static void	handle_env_var_expansion(const char *src, int *i, char **result)
{
	char	*tmp;
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (!src[*i] || (!ft_isalnum(src[*i]) && src[*i] != '_' && src[*i] != '?'))
	{
		tmp = ft_strjoin(*result, "$");
		free(*result);
		*result = tmp;
		return;
	}
	var_name = extract_var_name(src, i);
	var_value = getenv(var_name);
	if (!var_value)
		var_value = "";
	tmp = ft_strjoin(*result, var_value);
	free(*result);
	*result = tmp;
	free(var_name);
}

char	*expand_token_string(const char *src)
{
	int		i = 0;
	char	*result = ft_calloc(1, sizeof(char));
	char	*tmp;
	char	tmp_str[2];

	while (src[i])
	{
		if (src[i] == '$')
			handle_env_var_expansion(src, &i, &result);
		else
		{
			tmp_str[0] = src[i];
			tmp_str[1] = '\0';
			tmp = ft_strjoin(result, tmp_str);
			free(result);
			result = tmp;
			i++;
		}
	}
	return (result);
}


void is_env_var(t_input *input)
{
	t_input *curr = input;
	char	*expanded;

	expanded = expand_token_string(curr->token);
	input->token = expanded;
}

