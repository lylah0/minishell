/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 21:18:19 by moni              #+#    #+#             */
/*   Updated: 2025/03/14 16:53:25 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// affiche a tel endroit (fd) un caractere 
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*int main(void)
{
    // Voici où notre héroïque caractère 'a' prend la scène du terminal.
    ft_putchar_fd('a', 1);
    // Et tada! Un 'a' sauvage apparaît! 😄🎉
    return (0);
}*/