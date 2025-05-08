// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   export_T_CMD.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/04/01 21:49:28 by monoguei          #+#    #+#             */
// /*   Updated: 2025/05/08 13:53:47 by monoguei         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../../../../minishell.h"

// void lle_to_array(t_data *data)
// {
// 	char	**copy_env;
// 	t_env	*current;
// 	size_t		i;
// 	size_t		j;

// 	(void)copy_env;
// 	data->copy_env = malloc(sizeof(char **) * lle_size(data->env) + 1);
// 	if (!data->copy_env)
// 		return ;
// 	j = 0;
// 	current = data->env;
	
// 	while (current)
// 	{
// 		i = 0;
// 		while (ft_strlen(current->name) < i)
// 		{
// 			current->name[i] = data->copy_env[i][j];
// 			printf("%c", data->copy_env[i][j]);
// 			i++;
// 		}
// 		if (current->value)
// 		{
// 			data->copy_env[i][j] = '=';
// 			while (ft_strlen(current->name) + ft_strlen(current->value) < i)
// 			{
// 				current->name[i] = data->copy_env[i][j];

// 				i++;
// 			}
// 		}
// 		data->copy_env[i][j] = 0;
// 		i = 0;
// 		j++;
// 		current = current->next;
// 	}
// }


// void print_export(t_data *data)
// {
// 	int  i = 0;
// 	lle_to_array(data);
// 	// while (data->copy_env[i])
// 	// {
// 	// 	printf("%s\n", data->copy_env[i]);
// 	// 	i++;
// 	// }	
// 	// create_env_copy_array(data);
// 	// sort_words(data->copy_env, get_array_length(data->copy_env));
// 	// print_copy_env(data);
// }