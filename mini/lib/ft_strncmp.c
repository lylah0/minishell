/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:27:51 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:49:52 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// compare n caracteres entre deux strings
int	ft_strncmp(const char *first, const char *second, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (first[i] != second[i] || first[i] == '\0' || second[i] == '\0')
			return ((unsigned char)first[i] - (unsigned char)second[i]);
		i++;
	}
	return (0);
}
