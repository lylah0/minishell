/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fonctions_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:09:38 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/15 22:06:06 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Fonction qui imprime le type d'un seul token (comme précédemment)
// void	print_token_type(t_input *token)
// {
// 	if (!token)
// 	{
// 		printf("Token is NULL\n");
// 		return ;
// 	}
// 	switch (token->type)
// 	{
// 	case T_CMD:
// 		printf("Token type: T_CMD\n");
// 		break ;
// 	case T_ARG:
// 		printf("Token type: T_ARG\n");
// 		break ;
// 	case T_FILE:
// 		printf("Token type: T_FILE\n");
// 		break ;
// 		break ;
// 	case T_OP:
// 		printf("Token type: T_OP\n");
// 		break ;
// 	case T_PIPE:
// 		printf("Token type: T_PIPE\n");
// 		break ;
// 	case T_CMD_ARG:
// 		printf("Token type: T_CMD_ARG\n");
// 		break;
// 	case T_WORD:
// 		printf("Token type: T_WORD\n");
// 		break;
// 	default:
// 		printf("Unknown token type\n");
// 		break ;
// 	}
// }

// // Fonction pour imprimer tous les types dans une liste chaînée de tokens
// void	print_all_token_types(t_input *head)
// {
// 	t_input	*current;

// 	current = head;
// 	if (!current)
// 	{
// 		printf("No tokens in the list\n");
// 		return ;
// 	}
// 	while (current)
// 	{
// 		print_token_type(current); // Affiche le type du token actuel
// 		current = current->next;   // Passe au token suivant
// 	}
// }

// void	print_tokens(char **tokens)
// {
// 	int i = 0;

// 	printf("Tokens:\n");
// 	while (tokens[i])
// 	{
// 		printf("Token[%d]: %s\n", i, tokens[i]);
// 		i++;
// 	}
// }

//  void	print_token_list(t_input *head)
// {
// 	t_input	*curr = head;
// 	int		i = 0;

// 	printf("\n Vérification des tokens après expansion :\n");
// 	while (curr)
// 	{
// 		printf("Token[%d]: %s,(Type: %d)\n", i, curr->token, curr->type);
// 		curr = curr->next;
// 		i++;
// 	}
// 	printf("\n");
// }
