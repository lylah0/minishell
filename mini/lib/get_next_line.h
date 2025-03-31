/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moni <moni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 09:21:16 by moni              #+#    #+#             */
/*   Updated: 2024/05/02 15:01:17 by moni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*remove_line(char *line);
char	*extract_line(char *line);
char	*read_line(int fd, char *line);
size_t	ft_strlen(const char *s);
// char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr_newline(const char *s);

#endif