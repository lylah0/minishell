/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:33:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/01 21:50:15 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env_linked_list(t_data *data)
{
	t_env *temp = NULL;

	while (data->env)
	{
		temp = data->env->next;
		free(data->env->name);
		free(data->env->value);
		free(data->env);
		data->env = temp;
	}
}

void	print_env_linked_list(t_data *data)
{
	while (data->env)
	{
		printf("%s=", data->env->name);// pourquoi ca ne simprime pas si linked list imprimer aussi ? verifier coherence printf write
		printf("%s\n", data->env->value);// pourquoi ca ne simprime pas si linked list imprimer aussi ? verifier coherence printf write
		data->env = data->env->next;
	}
}

t_env	*create_env_linked_list(char **envp)
{
	int		i = 0;
	t_env	*current = NULL;
	t_env	*head = NULL;
	t_env	*temp = NULL;
	char	*separator;

	while (envp[i])
	{
		current = malloc(sizeof(t_env));
		if (!current)
		{
			free(current);
			return (0);
		}
		separator = ft_strchr(envp[i], '=');
		if (separator)
		{
			current->name = ft_substr(envp[i], 0, separator - envp[i]);
			current->value = ft_strdup(separator + 1);
		}
		else
		{
			current->name = ft_strdup(envp[i]);
			current->value = NULL;
		}
		current->next = NULL;
		if (!current->name || (separator && !current->value))
		{
			free(current->name);
			return (0);
		}
		if (!head)
			head = current;
		else
			temp->next = current;
		temp = current;
		i++;
	}
	return (head);
}

/// @brief 
/// @param data 
/// @param envp 
void	init_env(t_data *data, char **envp)
{
	data->env = create_env_linked_list(envp);
	//print_env_linked_list(data);
	// create_env_copy_array(data);
	// sort_words(data->copy_env, get_array_length(data->copy_env));
	//print_copy_env(data);
	// free_env_linked_list(data);
}
