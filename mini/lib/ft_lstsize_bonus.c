/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:59:28 by monoguei           #+#    #+#             */
/*   Updated: 2024/01/27 15:59:29 by monoguei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*lst_temp;

	if (!lst)
		return (0);
	lst_temp = lst;
	size = 0;
	while (lst_temp)
	{
		lst_temp = lst_temp->next;
		size++;
	}
	return (size);
}
