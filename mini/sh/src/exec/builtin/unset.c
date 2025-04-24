/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 10:35:40 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/24 21:22:14 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in `unset` `unset VAR1` `unset VAR1 VAR2`
/// @param data
void	b_unset(t_data *data)
{
	(void)data;
	t_env *env_to_del = NULL;

	while (data->env)
	{
		if (data->input->next->token && ft_strncmp(data->input->next->token, data->env->name, (ft_strlen(data->env->name))))
			env_to_del = data->env;
		data->env = data->env->next;
	}

	if (env_to_del)
		lle_del_one(env_to_del, (void *)lle_clear);
}
