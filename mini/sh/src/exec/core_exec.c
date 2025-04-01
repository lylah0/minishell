/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:25:16 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/01 16:30:21 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	kind_of_token(t_data *data, t_input *input)
{
	if (ft_strncmp_end((const char *)input, "echo", 4) == 0)
	{
		b_echo(input);
		return (0);
	}	
	else if (ft_strncmp_end((const char *)input, "cd", 2) == 0)
	{
		b_cd(data, input);
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "pwd", 3) == 0)
	{
		b_pwd();
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "env", 3) == 0)
	{
		b_env(data);
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "export", 6) == 0)
	{
		b_export(data);
		return (0);
	}
	else if (ft_strncmp_end((const char *)input, "unset", 5) == 0)
	{
		b_unset(data);
		return (0);
	}
	else // pas forcement arg, peut etre path/bin
		printf("%s = arg\n\n", input);
	return (1);
}