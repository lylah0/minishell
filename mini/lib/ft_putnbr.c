/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:28:48 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:53:04 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_exception(int *count)
{
	write(1, "-2147483648", 11);
	(*count) = (*count) + 11;
}

// imprime nombre
void	ft_putnbr(int n, int *count)
{
	int	digit;

	digit = 0;
	if (n == -2147483648)
		ft_exception(count);
	else if (n < 0)
	{
		ft_putchar('-', count);
		n = -n;
		ft_putnbr(n, count);
	}
	else
	{
		if (n > 9)
		{
			ft_putnbr(n / 10, count);
			ft_putnbr(n % 10, count);
		}
		else
		{
			digit = n + 48;
			ft_putchar(digit, count);
		}
	}
}
