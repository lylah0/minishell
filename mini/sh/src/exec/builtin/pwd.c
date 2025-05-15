/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:34:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 21:49:42 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	b_pwd(t_data *data)
{
	char	*pwd_value;

	pwd_value = search_env_value(data->env, "PWD");
	ft_printf("%s\n", pwd_value);
}
