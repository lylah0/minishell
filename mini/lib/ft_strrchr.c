/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:13:55 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:50:25 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// recherche la derniere occurence du searchedChar
char	*ft_strrchr(const char *str, int searchedChar)
{
	int	len;

	len = ft_strlen(str);
	if (str[len] == (char)searchedChar)
		return ((char *)&str[len]);
	while (len >= 0)
	{
		if (str[len] == (char)searchedChar)
			return ((char *)&str[len]);
		len--;
	}
	return (NULL);
}
