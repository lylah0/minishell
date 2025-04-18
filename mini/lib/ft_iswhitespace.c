/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:04:12 by monoguei          #+#    #+#             */
/*   Updated: 2025/04/18 17:46:06 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// verifie si un entier est un caracter de type "espace blanc"
int	ft_iswhitespace(int c)
{
	if (!(c == 32 || c == 9 || c == 10 || c == 13))
		return (0);
	return (1);
}
