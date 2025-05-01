/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:28:30 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/01 14:52:39 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_input	*tokenize(char **input, t_data *data)
{
	int		i;
	t_input	*tail;
	t_input	*head;
	t_input	*new_node;
	t_input	*current;

	i = 1;
	tail = malloc(sizeof(t_input));
	if (!tail)
		exit(1);
	tail->token = ft_strdup(input[0]);
	tail->prev = NULL;
	tail->next = NULL;
	head = tail;
	while (input[i])
	{
		new_node = malloc(sizeof(t_input));
		if (!new_node)
			exit(1);
		new_node->token = ft_strdup(input[i]);
		new_node->prev = tail;
		new_node->next = NULL;
		tail->next = new_node;
		tail = new_node;
		i++;
	}
	current = head;
	while (current)
	{
		current->type = get_token_type(current, current->token, data);
		current = current->next;
	}
	is_cmd_arg(head);
	return (head);
}

t_token_type	get_token_type(t_input *token, char *input, t_data *data)
{
	if (ft_strchr(input, '\'') || ft_strchr(input, '"') || ft_strchr(input,
			'$'))
	{
		parse_and_expand_token(token, data);
		return (T_WORD);
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
