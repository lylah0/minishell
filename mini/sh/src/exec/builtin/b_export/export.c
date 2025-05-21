/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 15:36:47 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../minishell.h"

static void	handle_export_no_args(t_data *data)
{
	if (!data->env || !data->env->name)
	{
		printf("Aucune variable d'environnement\n");
		printf("Initialisation d'un environnement vide...\n");
		data->env = malloc(sizeof * data->env);
		data->env->name = ft_strdup("Head_of_environnement");
		data->env->value = NULL;
		data->env->next = NULL;
		return ;
	}
	print_export(data);
}

static void	handle_export_assignment(t_data *data, char *token)
{
	char	*new_name;
	char	*new_value;

	new_name = extract_name(token);
	new_value = extract_value(token);
	if (!new_name || !new_value)
	{
		free(new_name);
		free(new_value);
		data->exit_code = 2;
		return ;
	}
	if (is_valid_env_name_var_syntax(new_name) == TRUE
		&& is_valid_env_value_syntax(new_value) == TRUE)
	{
		if (search_env_name(data->env, new_name) == NULL)
			add_new_env_var_and_value(data, new_name, new_value);
		else
			update_env_value(data, new_name, new_value);
	}
	else
		data->exit_code = 1;
	free(new_name);
	free(new_value);
}

static void	handle_export_name(t_data *data, char *token)
{
	if (is_valid_env_name_var_syntax(token) == TRUE)
		add_env_name(data, token);
	else
		data->exit_code = 1;
}

/// @brief builtin affiche, ajoute ou maj environnement
/// @example `export` `export NAME` `export NAME=` `export NAME=value`
/// `export NAME1=value NAME2=value`
/// @param data
void	b_export(t_data *data)
{
	t_input	*arg;

	arg = data->input->next;
	if (data->pipe_op == YES)
	{
		data->exit_code = 1;
		return ;
	}
	if (!arg || arg->type == T_PIPE)
		return (handle_export_no_args(data));
	while (arg && arg->type != T_PIPE)
	{
		if (ft_strchr(arg->token, '='))
			handle_export_assignment(data, arg->token);
		else
			handle_export_name(data, arg->token);
		arg = arg->next;
	}
}
