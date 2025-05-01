/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:40 by monoguei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/25 17:06:12 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/05/01 14:41:12 by monoguei         ###   ########.fr       */
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
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
		return;

	arg = (char *)data->input->next->token;
	if (!arg)
		return;

	current = data->env;
	prev = NULL;

	while (current)
	{
<<<<<<< HEAD
		if (ft_strncmp(arg, current->name) == 0)
=======
		if (ft_strncmp(arg, current->name, ft_strlen(current->name)) == 0)
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
		{
			if (prev)
				prev->next = current->next;
			else
				data->env = current->next;
			free(current->name);
			free(current->value);
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
<<<<<<< HEAD
}
// [ ] si env_var inexistant, message derreur
=======
}
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
