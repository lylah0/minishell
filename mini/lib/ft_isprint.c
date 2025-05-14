/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:25:05 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/14 16:53:57 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// vérifie si un entier est un caractère imprimable
int	ft_isprint(int character)
{
	if (32 <= character && character < 127)
		return (1);
	return (0);
}
