/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:16:10 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 09:27:29 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tab(char** tab)
{
	int	i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_token_list(t_input* head)
{
	t_input* tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->token)
			free(tmp->token);
		free(tmp);
	}
}

void	clean(t_data* data, char** splited_input, char* env_path, char* input)
{
	if (data->input)
	{
		free_token_list(data->input);
		data->input = NULL;
	}
	if (splited_input)
		free_tab(splited_input);
	if (env_path)
		free(env_path);
	if (input)
		free(input);
}

int	free_all(t_data* data)
{
	int	exit_code;

	exit_code = -1;
	if (!data)
		return (-1);
	if (data->copy_env)
		free_tab(data->copy_env);
	if (data->input)
		free_token_list(data->input);
	if (data->env)
		free_env_list(data->env);
	if (data->signal)
		free(data->signal);
	rl_clear_history();
	rl_free_line_state();
	rl_cleanup_after_signal();
	restore_terminal();
	exit_code = data->exit_code;
	if (data)
		free(data);
	return (exit_code);
}
