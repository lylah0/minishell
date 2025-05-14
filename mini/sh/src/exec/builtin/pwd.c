/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 10:34:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/11 18:16:20 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	b_pwd(t_data *data)
{
	char	*pwd_value;

	pwd_value = search_env_value(data->env, "PWD");
	ft_printf("%s\n", pwd_value);
}
// [OK] print pwd
