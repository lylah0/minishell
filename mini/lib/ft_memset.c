/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:55:03 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/14 16:53:32 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// remplit les n premiers octets de la mémoire pointée par s avec l'octet c
void	*ft_memset(void *ptr, int value, size_t count)
{
	size_t	i;

	i = 0;
	while (count > i)
	{
		((char *)ptr)[i] = value;
		i++;
	}
	return (ptr);
}
