/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 19:48:44 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/21 21:31:11 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	reset_signals_and_pipe(t_data *data, char *input)
{
	if (data->signal->sigint == ON)
		data->signal->sigint = OFF;
	if (data->signal->sigquit == ON)
		data->signal->sigquit = OFF;
	data->pipe_op = NO;
	if (!(ft_strchr(input, '|') == NULL && ft_strchr(input, '<') == NULL
			&& ft_strchr(input, '>') == NULL))
		data->pipe_op = YES;
}

t_signal	*init_signal_struct(void)
{
	t_signal	*signal;

	signal = malloc(sizeof(t_signal));
	if (!signal)
	{
		fprintf(stderr, "Error: Memory allocation failed for signal\n");
		return (NULL);
	}
	signal->sigint = OFF;
	signal->sigquit = OFF;
	return (signal);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		fprintf(stderr, "Error: Memory allocation failed\n");
		return (NULL);
	}
	data->input = NULL;
	data->env = NULL;
	data->copy_env = NULL;
	data->stdout_redir = 0;
	data->stdin_redir = 0;
	data->should_exit = 0;
	data->child_pid = -1;
	data->exit_code = 0;
	data->signal = init_signal_struct();
	if (!data->signal)
	{
		free(data);
		return (NULL);
	}
	return (data);
}
