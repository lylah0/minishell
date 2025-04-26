/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:40 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/26 12:40:37 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


/// @brief built-in `unset` `unset VAR1` `unset VAR1 VAR2`
/// @param data
void	b_unset(t_data *data)
{
	t_env	*current;
	t_env	*prev;
	char	*arg;

	if (!data || !data->input || !data->input->next)
	{
		perror("unset");
		return;
	}
	
	arg = (char *)data->input->next->token;
	if (!arg)
	{
		perror("!arg");
		return;
	}
	
	printf("unset\n");
	current = data->env;
	prev = NULL;

	while (current)
	{
		if (ft_strncmp(arg, current->name, ft_strlen(current->name)) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				data->env = current->next;
			lle_del_one(current, free);
			print_lle(data);

			return;
		}
		prev = current;
		current = current->next;
	}
}
// [ ] si env_var inexistant, message derreur
