/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:58:54 by monoguei          #+#    #+#             */
/*   Updated: 2025/05/22 09:40:34 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*lst_last;

	if (!lst)
		return (0);
	lst_last = lst;
	while (lst_last->next)
		lst_last = lst_last->next;
	return (lst_last);
}
