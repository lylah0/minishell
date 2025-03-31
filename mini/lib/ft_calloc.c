/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:14:49 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:54:20 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n);

// alloue de la mémoire pour un tableau d'éléments, tous initialisés à zéro
void	*ft_calloc(size_t nb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (nb == 0 || size == 0 || nb > (~(size_t)0 / size))
		return (NULL);
	total_size = nb * size;
	ptr = malloc(total_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
