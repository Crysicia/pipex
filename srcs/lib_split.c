/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 03:21:27 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:21:41 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	sub_len;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub_len = ft_strlen(&s[start]);
	if (sub_len > len)
		sub_len = len;
	str = malloc((sub_len + 1) * sizeof(char));
	if (str)
		ft_strlcpy(str, &s[start], sub_len + 1);
	return (str);
}

void	*ft_free_matrix(void **matrix, size_t size)
{
	size_t	index;

	index = 0;
	while (index < size)
	{
		free(matrix[index]);
		index++;
	}
	free(matrix);
	return (NULL);
}

static size_t	ft_count_words(char const *str, char sep)
{
	size_t	index;
	size_t	count;

	index = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[index])
	{
		while (str[index] == sep)
			index++;
		if (str[index] != sep && str[index])
			count++;
		while (str[index] != sep && str[index])
			index++;
	}
	return (count);
}

static size_t	ft_word_len(char const *str, char sep)
{
	size_t	length;

	length = 0;
	while (str[length] != sep && str[length])
		length++;
	return (length);
}

char	**ft_split(char const *s, char c)
{
	size_t	index;
	size_t	arr_i;
	char	**arr;

	index = 0;
	arr_i = 0;
	if (!s)
		return (NULL);
	arr = malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (arr_i < ft_count_words(s, c))
	{
		while (s[index] == c)
			index++;
		arr[arr_i] = ft_substr(s, index, ft_word_len(&s[index], c));
		if (!arr[arr_i])
			return (ft_free_matrix((void **)arr, arr_i + 1));
		index += ft_word_len(&s[index], c);
		arr_i++;
	}
	arr[arr_i] = NULL;
	return (arr);
}
