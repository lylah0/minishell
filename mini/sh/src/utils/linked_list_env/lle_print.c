/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lle_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:11:18 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 19:11:57 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief Prints the environment linked list.
/// @param data Pointer to the data structure containing the environment list.
void	print_lle(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		printf("%s", current->name);
		if (current->value)
			printf("=%s\n", current->value);
		else
			printf("\n");
		current = current->next;
	}
}
