/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 09:21:29 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/22 16:38:45 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/// @brief built-in `exit` `exit N` `exit arg` `exit arg1 arg2`
/// @param data 
void	b_exit(t_data *data)
{
	// if (no_arg)
	// 	"exit";
	// 	exit(0);
	// else if (more than 1 arg)
	// 	`bash: exit: too many arguments`;
	// 	exit_status = 1; // on ne quitte pas le programme 
	// else 
	// 	if num 
	// 		exit(n % 256);
	// 	else
	// 		`bash: exit: 42abc: numeric argument required`;
	// 		exit(255);

	// cleanup_memory(data->input);
(void)data;
	printf("exit\n");
	exit(0);
}

// [ ] a coder...