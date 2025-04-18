/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 14:38:25 by lylrandr          #+#    #+#             */
/*   Updated: 2025/04/18 16:55:24 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	redir(t_data *data, t_input *current)
{
	(void)data;
	(void)current;
//	if (current->token == '<' || current->token == '>')
//		simple_redir(data, current);
//	else
//		heredoc_append(data, current);
}

void	simple_redir(t_data *data, t_input *current)
{
		(void)data;
	(void)current;

	//if (current->token == '>')
	//{
//
	//}
	//else
	//{
//
	//}
}

void	heredoc_append(t_data *data, t_input *current)
{
	(void)data;
	(void)current;

}
