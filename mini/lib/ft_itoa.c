/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:23:06 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:53:50 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// conversion int -> ASCII
static int	ft_intlen(int n)
{
	int	len;

	if (n <= 0)
		len = 1;
	else
		len = 0;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	fill_str(char *ptr, int n)
{
	int	size_char;

	size_char = ft_intlen(n);
	ptr[size_char--] = '\0';
	if (n == 0)
	{
		ptr[0] = '0';
		return ;
	}
	if (n < 0)
	{
		ptr[0] = '-';
		if (n == -2147483648)
		{
			ptr[size_char--] = '8';
			n /= 10;
		}
		n = -n;
	}
	while (n != 0)
	{
		ptr[size_char--] = '0' + (n % 10);
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		size_char;

	size_char = ft_intlen(n);
	ptr = malloc(sizeof(char) * (size_char + 1));
	if (!ptr)
		return (NULL);
	fill_str(ptr, n);
	return (ptr);
}
