/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_stderr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:29:49 by moni              #+#    #+#             */
/*   Updated: 2025/05/15 21:53:39 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, 1);
}

void	ft_printf_stderr(const char *s, ...)
{
	int			i;
	va_list		ap;
	char		*str;

	va_start(ap, s);
	i = 0;
	while (s[i])
	{
		if (s[i] == '%')
		{
			i++;
			str = va_arg(ap, char *);
			if (str)
				ft_putstr_fd(str, 2);
			else
				ft_putstr_fd("(null)", 2);
		}
		else
			ft_putchar_fd(s[i], 2);
		i++;
	}
	va_end(ap);
}

