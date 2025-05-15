/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:51:39 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/15 21:52:42 by monoguei         ###   ########.fr       */
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

	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("0"));
	}
	while (ft_isalnum(str[*i + len]) || str[*i + len] == '_')
		len++;
	name = ft_substr(str, *i, len);
	*i += len;
	return (name);
}

static void	handle_env_var_expansion(const char *src, int *i, char **result, t_data *data)
{
	char	*var_name;
	char	*var_value;

	(*i)++;
	if (src[*i] == '?')
	{
		(*i)++;
		var_value = ft_strdup("0");  // temporairement 0
		safe_strjoin_replace(result, var_value);
		free(var_value);
		return;
	}
	if (!src[*i] || (!ft_isalnum(src[*i]) && src[*i] != '_'))
	{
		safe_strjoin_replace(result, "$");
		return;
	}
	var_name = extract_var_name(src, i);
	var_value = my_getenv(data, var_name);
	if (!var_value)
		var_value = "";
	append_str_to_result(result, var_value);
	free(var_name);
}

char	*expand_token_string(const char *src, t_data *data)
{
	int		i;
	char	*result;
	char	*tmp;
	char	tmp_str[2];
	char	*old;

	i = 0;
	result = ft_calloc(1, sizeof(char));
	if (!result)
		return (NULL);
	while (src[i])
	{
		if (src[i] == '$')
		{
			handle_env_var_expansion(src, &i, &result, data);
			continue;
		}
		else
		{
			tmp_str[0] = src[i];
			tmp_str[1] = '\0';
			tmp = ft_strjoin(result, tmp_str);
			old = result;
			result = tmp;
			free(old);
			i++;
		}
	}
	return (result);
}

void is_env_var(t_input *input, t_data *data)
{
	t_input	*curr;
	char	*expanded;

	expanded = expand_token_string(curr->token, data);
	free(input->token);
	input->token = expanded;
}
