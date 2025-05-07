/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:07:22 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/07 18:19:07 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_memory(char *line, char **splited_line)
{
	int	j;

	free(line);
	j = 0;
	while (splited_line[j])
	{
		if (splited_line[j])
			free(splited_line[j]);
		j++;
	}
	free(splited_line);
}

/// @brief
/// @param s1
/// @param s2
/// @param n
/// @return
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n && (s1[i] || s2[i]))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}

// copie colle avec malloc ET ajoute = a la fin
char	*ft_strdup_equal(const char *src)
{
	int		i;
	int		j;
	int		len;
	char	*dest;

	// if(!src)
		// return();
	i = 0;
	j = 0;
	len = ft_strlen(src);
	dest = (char *)malloc((len + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	dest[j] = '=';
	while (src[i] != 0)
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	dest[++j] = 0;
	return (dest);
}
// export NAME=
// export NAME


// Concatène str dest+src mod moni
// return taille tot
size_t	ft_strcat(char *dest, const char *src)
{
	size_t	src_len;
	size_t	dest_len;
	size_t	i;
	size_t	size;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	size = src_len + dest_len;
	i = 0;
	if (size <= dest_len)
		return (src_len + size);
	while (src[i] != 0 && (dest_len + i) < (size - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (size > 0)
		dest[dest_len + i] = 0;
	return (dest_len + src_len);
}

int	ft_strncmp_end(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n && (s1[i] || s2[i]))
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	return (0);
}
// int	ft_strncmp_end(char *s1, char *s2, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (0);
// 	if (ft_strlen(s1) == n)
// 	{
// 		while (s1[i] && s2[i] && n > 1)
// 		{
// 			if (s1[i] != s2[i])
// 				return ((char)s1[i] - (char)s2[i]);
// 			i++;
// 			n--;
// 		}
// 		return (0);
// 	}
// 	else
// 		return (-1);
// }

// copie colle avec malloc
char	*ft_strdup(const char *src)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(src);
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	if (dest == NULL)
	{
		free(dest);
		exit_code = 1;
	}	
	return (dest);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	src_len = 0;
	while (src[src_len])
		src_len++;
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (src_len);
}

t_input	*cat_token(t_input *token, char *value, int len)
{
	t_input	*new_token;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	new_token = malloc(sizeof(t_input));
	if (!new_token)
		return (NULL);
	new_token->token = malloc(sizeof(char) * (len + 1));
	if (!new_token->token)
	{
		free(new_token);
		return (NULL);
	}
	while (token->token[i] && token->token[i] != '$')
	{
		new_token->token[j] = token->token[i];
		i++;
		j++;
	}
	while (value[k])
	{
		new_token->token[j] = value[k];
		k++;
		j++;
	}
	new_token->token[j] = '\0';
	return (new_token);
}

