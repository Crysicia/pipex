/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 03:24:20 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:24:30 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	if (src == dst)
		return (dst);
	while (index < n)
	{
		*(char *)(dst + index) = *(char *)(src + index);
		index++;
	}
	return (dst);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;
	size_t	index;

	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	index = 0;
	if (dstsize == 0)
		return (srclen);
	if (dstsize == dstlen)
		return (srclen + dstlen);
	if (dstsize < dstlen)
		return (dstsize + srclen);
	while (index + dstlen < dstsize - 1 && src[index])
	{
		dst[dstlen + index] = src[index];
		index++;
	}
	dst[dstlen + index] = '\0';
	return (srclen + dstlen);
}
