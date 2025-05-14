/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:22:01 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:50:40 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copie n caracteres
char	*ft_strncpy(char *dest, const char *src, size_t size)
{
	int	i;

	i = 0;
	while (src[i] != 0 && size > 0)
	{
		dest[i] = src[i];
		i++;
		size--;
	}
	dest[i] = 0;
	return (dest);
}
