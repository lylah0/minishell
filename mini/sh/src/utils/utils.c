/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoguei <monoguei@student.lausanne42.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:07:22 by lylrandr          #+#    #+#             */
/*   Updated: 2025/05/20 22:10:04 by monoguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

// Duplique src et ajoute '=' à la fin (ex: src="HOME" -> "HOME=")
char	*ft_strdup_equal(const char *src)
{
    int		i;
    int		len;
    char	*dest;

    if (!src)
        return (NULL);
    len = ft_strlen(src);
    dest = (char *)malloc((len + 2) * sizeof(char)); // +1 pour '=' et +1 pour '\0'
    if (!dest)
        return (NULL);
    for (i = 0; i < len; i++)
        dest[i] = src[i];
    dest[len] = '=';
    dest[len + 1] = '\0';
    return (dest);
}

// Duplique src en ajoutant '=' au début (ex: src="HOME" -> "=HOME")
char	*ft_equal_strdup(const char *src)
{
    int		i;
    int		len;
    char	*dest;

    if (!src)
        return (NULL);
    len = ft_strlen(src);
    dest = (char *)malloc((len + 2) * sizeof(char)); // +1 pour '=' et +1 pour '\0'
    if (!dest)
        return (NULL);
    dest[0] = '=';
    for (i = 0; i < len; i++)
        dest[i + 1] = src[i];
    dest[len + 1] = '\0';
    return (dest);
}

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


char	*ft_strndup(const char *src, int n)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = ft_strlen(src);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
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

int	str_isdigit(char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*strjoin_name_equal_value(char *name, char *value)
{
	int i = 0;
	int j = 0;
	int tot_len;
	if (value)
		tot_len = ft_strlen(name) + ft_strlen(value) + 4;// = , \0 , " , "
	else
		tot_len = ft_strlen(name) + 1;
	char *s = malloc(sizeof(char) * tot_len);
	if (!s)
		return NULL;
	while (name[i])
	{
		s[i] = name[i];
		i++;
	}
	if (value)
	{
		s[i++] = '=';
		s[i++] = '"';
		while (value[j])
			s[i++] = value[j++];
		s[i++] = '"';
		}
	s[i] = '\0';
	return (s);
}

void	swap_words(char **a, char **b)
{
	char *temp;
	temp = NULL;

	temp = *a;
	*a = *b;
	*b = temp;
}