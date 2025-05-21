/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:51:39 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 21:34:29 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*safe_strjoin_replace(char **dest, const char *suffix)
{
	char	*tmp;
	char	*safe_src;

	if (!suffix)
		return (*dest);
	if (*dest)
		safe_src = ft_strdup(*dest);
	else
		safe_src = ft_strdup("");
	if (!safe_src)
		return (NULL);
	tmp = ft_strjoin(safe_src, suffix);
	free(safe_src);
	if (*dest)
		free(*dest);
	*dest = tmp;
	return (*dest);
}

char	*extract_var_name(const char *str, int *i)
{
	int		len;
	char	*name;

	len = 0;
	while (ft_isalnum(str[*i + len]) || str[*i + len] == '_')
		len++;
	name = ft_substr(str, *i, len);
	*i += len;
	return (name);
}

static void	handle_env_var_expansion(const char *src, int *i, char **result,
		t_data *data)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (handle_special_cases(src, i, result))
		return ;
	var_name = extract_var_name(src, i);
	var_value = search_env_value(data->env, var_name);
	if (!var_value)
		var_value = "";
	append_str_to_result(result, var_value);
	free(var_name);
}

char	*expand_token_string(const char *src, t_data *data)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
			handle_env_var_expansion(src, &i, &result, data);
		else
			append_char_to_result(&result, src[i++]);
	}
	return (result);
}

void	is_env_var(t_input *input, t_data *data)
{
	t_input	*curr;
	char	*expanded;

	curr = input;
	expanded = expand_token_string(curr->token, data);
	free(input->token);
	input->token = expanded;
}
