/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:45 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/01 22:00:07 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in `export` `export VAR=value` `export VAR` `export VAR+=value`
/// @param data 
void    b_export(t_data *data)
{
	// t_input    *curr;

	// curr = data->input;
	// 	if (!curr->next)// `export`
	// 	{
			create_env_copy_array(data);
			sort_words(data->copy_env, get_array_length(data->copy_env));
			print_copy_env(data);
		// }
		// else
		// 	printf("hello");
}

/// @brief version head -|- built-in `export` `export VAR=value` `export VAR` `export VAR+=value`
/// @param data 
void    c_export(t_input *head)
{
	t_data *data = head->data;

	if (!head->next)// `export`
	{
		create_env_copy_array(data);
		sort_words(data->copy_env, get_array_length(data->copy_env));
		print_copy_env(data);
	}
	else
	{
		printf("hello");
		// if (is_valid_env_var_syntax(```T_ARG```) == TRUE)
		// {
		// 	add_env_var(```T_ARG```);// add ou maj NAME=value
		// }
	}
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