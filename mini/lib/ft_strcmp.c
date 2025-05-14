/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 17:00:00 by monoguei          #+#    #+#             */
/*   Updated: 2025/03/14 16:51:12 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// compare deux chaînes de caractères
int	ft_strcmp(const char *first, const char *second)
{
	int	i;

	i = 0;
	while (first[i] == second[i] && first != 0 && second != 0)
		i++;
	return (first[i] - second[i]);
}
