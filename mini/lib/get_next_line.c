/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moni <moni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 10:20:04 by moni              #+#    #+#             */
/*   Updated: 2024/03/25 15:09:00 by moni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

char	*read_line(int fd, char *line)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr_newline(line) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		line = ft_strjoin(line, buffer);
	}
	free(buffer);
	return (line);
}

char	*extract_line(char *line)
{
	char	*extracted_line;
	int		i;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	extracted_line = (char *)malloc(i + 2);
	if (!extracted_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		extracted_line[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		extracted_line[i] = line[i];
		i++;
	}
	extracted_line[i] = '\0';
	return (extracted_line);
}

char	*remove_line(char *line)
{
	char	*text_after_extraction;
	size_t	len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	len = ft_strlen(line) - i;
	text_after_extraction = (char *)malloc(len + 1);
	if (!text_after_extraction)
		return (NULL);
	i++;
	while (line[i])
		text_after_extraction[j++] = line[i++];
	text_after_extraction[j] = '\0';
	free(line);
	return (text_after_extraction);
}

char	*get_next_line(int fd)
{
	static char	*static_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, 0, 0) == -1)
	{
		free(static_buffer);
		static_buffer = NULL;
		return (NULL);
	}
	static_buffer = read_line(fd, static_buffer);
	if (!static_buffer)
		return (NULL);
	line = extract_line(static_buffer);
	static_buffer = remove_line(static_buffer);
	return (line);
}

/*	read_line:
	Reads data from the file specified by fd into a buffer, concatenates it to
	'line' until a newline character ('\n') or the end of the file is found.
	Frees the temporary buffer and returns the accumulated string. */

/*	extract_line:
	Extracts the first line (up to the first '\n', inclusive) from the string
	'line'. Allocates and returns a new string containing this extracted line.
	*/

/*	remove_line:
	Removes the first line from the string 'line' and returns the rest. If 
	'line' starts with a '\n', this function creates a new string without this
	leading '\n' and the preceding part of 'line', freeing the old string. */

/*	get_next_line:
	The main function that uses a static buffer to accumulate data read from
	the file descriptor 'fd'. It reads data by calling read_line, extracts the
	first available line with extract_line, and updates the static buffer by
	removing this line with remove_line. Returns the extracted line or NULL if
	the end of the file is reached or in case of an error. */