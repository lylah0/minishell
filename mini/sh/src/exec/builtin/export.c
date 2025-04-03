/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/02 20:05:42 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief version head -|- built-in `export` `export VAR=value` `export VAR` `export VAR+=value`
/// @param data 
void    b_export(t_data *data)
{
	if (data->input->type == 0)// `export`[ ] et la suite est .. ?
	{
		create_env_copy_array(data);
		sort_words(data->copy_env, get_array_length(data->copy_env));
		print_copy_env(data);
	}
	else if (data->input->type == 1)
	{
		if (is_valid_env_var_syntax(data->input->next->token) == TRUE)
		{
			printf("export.c > b_export : \t %s is a valid env var SYNTAXE :)\n", data->input->next->token);
			add_env_var(data, data->input->next->token);// add ou maj NAME=value
		}
	}
	else 
		return ;
}
// int main(int ac, char **av, char **envp)
// {
// 	t_data	*data = malloc(sizeof(t_data));
// 	if(!data)
// 		return 0;
// 	(void)ac;
// 	(void)av;
// 	init_env(data, envp);
// 	// b_env(data);
// 	// b_export(data);
// }