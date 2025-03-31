/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moni <moni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:42:31 by moni              #+#    #+#             */
/*   Updated: 2024/05/02 15:19:31 by moni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_newline(const char *s)
{
	if (s == NULL)
		return (NULL);
	while (*s)
	{
		if (*s == '\n')
			return ((char *)s);
		s++;
	}
	return (NULL);
}

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*dest;
// 	size_t	i;
// 	size_t	j;

// 	i = -1;
// 	j = 0;
// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 	{
// 		s1 = (char *)malloc(sizeof(char) * 1);
// 		s1[0] = '\0';
// 	}
// 	dest = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
// 	if (!dest)
// 		return (NULL);
// 	while (s1[++i])
// 		dest[i] = s1[i];
// 	while (s2[j])
// 		dest[i++] = s2[j++];
// 	dest[i] = '\0';
// 	free(s1);
// 	return (dest);
// }

// In ft_strchr_newline, I've adapted strchr for clarity: it specifically 
// looks for '\n'.

// In ft_strjoin, s1 is freed at line 59. This is specific to its use in GNL
// where s1 holds data that has already been read and accumulated. After
// concatenation with s2, s1 is no longer needed, so freeing s1 helps prevent
// memory leaks.