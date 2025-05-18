/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 21:33:51 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/18 13:39:55 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lle(t_data *data)
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

void	print_lle(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		printf("%s", current->name);// pourquoi ca ne simprime pas si linked list imprimer aussi ? verifier coherence printf write
		if (current->value)
			printf("=%s\n", current->value);// pourquoi ca ne simprime pas si linked list imprimer aussi ? verifier coherence printf write
		else
			printf("\n");
		current = current->next;
	}
}

void	free_env_list(t_env *head)
{
    t_env *tmp;
    while (head)
    {
        tmp = head->next;
        free(head->name);
        free(head->value);
        free(head);
        head = tmp;
    }
}



t_env	*create_lle(char **envp)
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
			free(current->value);
			free(current);
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

t_env	*create_lle_empty(t_env *env)
{
	t_env	*current = NULL;

	current = env;
	current = malloc(sizeof(t_env));
	if (!current)
	{
		free(current);
		return (0);
	}
	current->name = ft_strdup("");
	current->value = NULL;
	current->next = NULL;
	return (current);
}

void	init_env(t_data *data, char **envp)
{
	data->env = create_lle(envp);
	if(!data->env)
    {
        // on force l’allocation d’une liste vide (sentinel)
        data->env         = malloc(sizeof *data->env);
        data->env->name   = NULL;
        data->env->value  = NULL;
        data->env->next   = NULL;
		return ;
	}
}
