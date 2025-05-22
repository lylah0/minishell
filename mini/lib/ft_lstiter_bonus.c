/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:58:08 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/22 09:45:22 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*lst_temp;

	if (!lst || !f)
		return ;
	lst_temp = lst;
	while (lst_temp)
	{
		(*f)(lst_temp->content);
		lst_temp = lst_temp->next;
	}
}
