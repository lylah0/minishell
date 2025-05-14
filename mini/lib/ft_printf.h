/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moni <moni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:48:52 by moni              #+#    #+#             */
/*   Updated: 2023/12/08 11:59:14 by moni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
void	ft_putchar(char c, int *count);
void	ft_putnbr_hex_ptr(unsigned long nbr, int *count);
void	ft_putnbr_hex_xlo(int nb, int *count);
void	ft_putnbr_hex_xup(int nb, int *count);
void	ft_putnbr_u(unsigned int nb, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putptr(void *ptr, int *count);
void	ft_putstr(char *str, int *count);

#endif