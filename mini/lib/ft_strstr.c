/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:35:43 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:50:22 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// compare deux strings
char	*ft_strstr(char *fullstr, char *substr)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = 0;
	while (fullstr[i])
	{
		while (fullstr[i] == substr[j])
		{
			i++;
			j++;
		}
		if (substr[j])
		{
			start = i - j;
			return (&fullstr[start]);
		}
		i++;
	}
	return (NULL);
}
