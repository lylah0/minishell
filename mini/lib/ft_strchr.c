/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:57:53 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/04 16:05:17 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Recherche la première occurrence de searchedChar dans la str passée en param.

/// @brief Searches for the first occurrence of a character in a string.
/// @param str The string to be searched.
/// @param searchedChar The character to search for.
/// @return A pointer to the first occurrence of the character in the string, 
/// or NULL if the character is not found.
char	*ft_strchr(const char *str, int searchedChar)
{
	size_t	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if ((unsigned char)str[i] == (unsigned char)searchedChar)
			return ((char *)&str[i]);
		i++;
	}
	if (searchedChar == 0)
		return ((char *)&str[i]);
	return (NULL);
}
