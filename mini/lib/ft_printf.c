/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moni <moni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:29:49 by moni              #+#    #+#             */
/*   Updated: 2023/12/08 13:35:19 by moni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

void	ft_define_type(char s, va_list ap, int *count)
{
	if (s == 'c')
		ft_putchar (va_arg(ap, int), count);
	else if (s == 'i' || s == 'd')
		ft_putnbr(va_arg(ap, int), count);
	else if (s == 's')
		ft_putstr(va_arg(ap, char *), count);
	else if (s == 'p')
		ft_putptr(va_arg(ap, void *), count);
	else if (s == 'u')
		ft_putnbr_u(va_arg(ap, unsigned int), count);
	else if (s == 'x')
		ft_putnbr_hex_xlo(va_arg(ap, unsigned int), count);
	else if (s == 'X')
		ft_putnbr_hex_xup(va_arg(ap, unsigned int), count);
	else if (s == '%')
		ft_putchar(('%'), count);
	else
	{
		ft_putchar(('%'), count);
		ft_putchar((s), count);
	}
}

int	ft_printf(const char *s, ...)
{
	int			i;
	va_list		ap;
	int			count;

	count = 0;
	va_start (ap, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			ft_define_type(s[i], ap, &count);
		}
		else
			ft_putchar((s[i]), &count);
		i++;
	}
	va_end(ap);
	return (count);
}
