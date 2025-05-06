/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:14:34 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/08 14:14:23 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int character);

int	ft_iswhitespace(int c)
{
	if (c == 32 || c == 9 || c == 10 || c == 11 || c == 12 || c == 13)
	return (1);
	return (0);
}

// convertir char en int
int	ft_atoi(const char *str)
{
	int	i;
	int	minus;
	int	nb;

	i = 0;
	minus = 1;
	nb = 0;
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]))
	{
		nb = (nb * 10) + str[i] - 48;
		i++;
	}
	return (minus * nb);
}
/*
int	main(void)
{
	printf("%d", ft_atoi("+1"));
	return (0);
}*/
