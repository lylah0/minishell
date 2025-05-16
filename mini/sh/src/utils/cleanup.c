/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 14:16:10 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/16 16:58:40 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	cleanup_memory(char *line, char **splited_line)
{
	int	j;

	j = 0;
	free(line);
	while (splited_line[j])
	{
		if (splited_line[j])
			free(splited_line[j]);
		j++;
	}
	free(splited_line);
}

void	free_token_list(t_input *head)
{
	t_input *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->token)
			free(tmp->token);
		free(tmp);
	}
}

void	free_env_list(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	clean(t_data *data, char **splited_input, char *env_path, char *input)
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
