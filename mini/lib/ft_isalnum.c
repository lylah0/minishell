/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lylrandr <lylrandr@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:19:52 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/19 14:00:54 by lylrandr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// vérifie si un entier est un caractère alphabetiquenumerique
int	ft_isalnum(int c)
{
	if (!(ft_isdigit(c) || ft_isalpha(c)))
		return (0);
	return (1);
}
