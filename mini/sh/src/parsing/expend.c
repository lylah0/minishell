/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:51:39 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/22 15:34:39 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
// static void	handle_env_var_expansion(t_env *env, const char *src, int *i, char **result)
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
	var_value = getenv(var_name); //TO DO : utiliser env du programme et pas du pc
	// t_env *current = search_env_name(env, var_name);// ajouter t_env *env au prototype
	// var_value = current->value;// va chercher la value de lenv du shell original et ne reprend donc pas les modifications apportees a notre env de minishell
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
	char	*result;
	char	*tmp;
	char	tmp_str[2];

	result = ft_calloc(1, sizeof(char));
	while (src[i])
	{
		if (src[i] == '$')
			handle_env_var_expansion(src, &i, &result);
		else
		{
			tmp_str[0] = src[i];
			tmp_str[1] = '\0';
			tmp = ft_strjoin(result, tmp_str);
//			free(result);
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

