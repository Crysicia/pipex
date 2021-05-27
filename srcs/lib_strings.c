/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_strings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 03:22:55 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:23:09 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	index;

	index = 0;
	while (s[index])
		index++;
	return (index);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s1) + 1;
	dup = malloc(len * sizeof(char));
	if (dup)
		ft_memcpy(dup, s1, len);
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	index;
	size_t	s_len;

	index = -1;
	s_len = 0;
	while (s[s_len])
		s_len++;
	while (++index <= s_len)
		if (s[index] == (char)c)
			return ((char *)&s[index]);
	return (NULL);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	if (n == 0)
		return (0);
	index = 0;
	while (s1[index] && s1[index] == s2[index] && index < n - 1)
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	srcsize;
	size_t	index;

	srcsize = 0;
	index = 0;
	if (dst == NULL && src == NULL)
		return (0);
	while (src[srcsize])
		srcsize++;
	if (dstsize == 0)
		return (srcsize);
	while (index < dstsize - 1 && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
	return (srcsize);
}
