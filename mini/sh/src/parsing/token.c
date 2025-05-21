/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:28:30 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/21 13:10:44 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/// @brief
/// @param tail
/// @param token_str
/// @return
t_input	*add_token(t_input *tail, char *token_str)
{
	t_input	*new_node;

	new_node = malloc(sizeof(t_input));
	if (!new_node)
	{
		tail->data->exit_code = 1;
		return (NULL);
	}
	new_node->token = NULL;
	new_node->prev = NULL;
	new_node->next = NULL;
	if (token_str)
		new_node->token = ft_strdup(token_str);
	new_node->prev = tail;
	if (tail)
		tail->next = new_node;
	return (new_node);
}

void	assign_token_types(t_input *head, t_data *data)
{
	t_input	*current;

	current = head;
	while (current)
	{
		current->type = get_token_type(current, current->token, data);
		current = current->next;
	}
	current = head;
	while (current)
	{
		if (current->token && current->token[0] == '\0')
			current->type = T_SKIP;
		current = current->next;
	}
}

t_input	*tokenize(char **input, t_data *data)
{
	int		i;
	t_input	*tail;
	t_input	*head;

	i = 1;
	tail = malloc(sizeof(t_input));
	if (!tail)
	{
		perror("tokenize");
		exit(1);
	}
	tail->token = ft_strdup(input[0]);
	tail->prev = NULL;
	tail->next = NULL;
	head = tail;
	while (input[i])
	{
		tail = add_token(tail, input[i]);
		i++;
	}
	assign_token_types(head, data);
	is_cmd_arg(head);
	return (head);
}

t_token_type	get_token_type(t_input *token, char *input, t_data *data)
{
	if (ft_strchr(input, '\'') || ft_strchr(input, '"') || ft_strchr(input,
			'$'))
	{
		parse_and_expand_token(token, data);
		return (token->type);
	}
	if (ft_strncmp(input, "|", 1) == 0)
		return (T_PIPE);
	else if (ft_strncmp(input, "<", 1) == 0 || ft_strncmp(input, ">", 1) == 0
		|| ft_strncmp(input, ">>", 2) == 0 || ft_strncmp(input, "<<", 2) == 0)
		return (T_OP);
	else if (token->prev != NULL && token->prev->type == T_OP)
		return (T_FILE);
	else if (token->prev != NULL && (token->prev->type == T_CMD
			|| token->prev->type == T_ARG || token->prev->type == T_WORD))
		return (T_ARG);
	return (T_CMD);
}

void	is_cmd_arg(t_input *token)
{
	t_input	*curr;

	curr = token;
	while (curr)
	{
		if (curr->type == T_CMD && curr->next && curr->next->type == T_ARG)
			curr->type = T_CMD_ARG;
		curr = curr->next;
	}
}
