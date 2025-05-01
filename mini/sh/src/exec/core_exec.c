/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:25:16 by monoguei          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/01 15:08:38 by monoguei         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2025/04/25 17:00:59 by monoguei         ###   ########.fr       */
=======
/*   Updated: 2025/05/01 14:40:34 by monoguei         ###   ########.fr       */
>>>>>>> 74eb669b58f6d41c2f4459b5b95133d259260ddc
>>>>>>> eb617a4c514e795db0ef1fe9f6c22ce25ebbf2de
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	kind_of_token(t_data *data, t_input *input)
{
	char	*input_str;
	input_str = input->token;

	if (ft_strncmp_end(input_str, "echo", 4) == 0)
	{
		b_echo(input);
		return (0);
	}
	if (ft_strncmp_end(input_str, "exit", 4) == 0)
	{
		b_exit(data);
		return (0);
	}
	else if (ft_strncmp_end(input_str, "cd", 2) == 0)
	{
		b_cd(data);
		b_cd(data);
		return (0);
	}
	else if (ft_strncmp_end(input_str, "pwd", 3) == 0)
	{
		b_pwd(data);
		b_pwd(data);
		return (0);
	}
	else if (ft_strncmp_end(input_str, "env", 3) == 0)
	{
		b_env(data);
		return (0);
	}
	else if (ft_strncmp_end(input_str, "unset", 5) == 0)
	{
		b_unset(data);
		return (0);
	}
	else if (ft_strncmp_end(input_str, "export", 6) == 0)
	{
		b_export(data);
		return (0);
	}
	else // pas forcement arg, peut etre path/bin
//		printf("core_exec.c > kind_of_token :\t***VERY USEFULL INFORMATION*** : is a cmd/path :)\n\n");
	return (1);
}
