/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:40 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/30 13:50:01 by lylrandr         ###   ########.fr       */
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
		if (ft_strncmp(arg, current->name, ft_strlen(arg)) == 0)
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
}
// [ ] si env_var inexistant, message derreur
