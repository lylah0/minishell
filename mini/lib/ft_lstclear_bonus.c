/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:57:46 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/22 09:45:06 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*lst_temp;

	if (!*lst)
		return ;
	while (*lst)
	{
		lst_temp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lst_temp;
	}
}
