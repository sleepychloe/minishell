/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/23 11:52:03 by yhwang            #+#    #+#             */
/*   Updated: 2021/07/26 13:37:17 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **res)
{
	unsigned int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static unsigned int	word_count(char const *s, char c)
{
	unsigned int	i;
	unsigned int	cnt;

	if (!s[0])
		return (0);
	i = 0;
	cnt = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			cnt++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		cnt++;
	return (cnt);
}

static void	put_res(char **src, unsigned int *len_of_w, char c)
{
	unsigned int	i;

	*src += *len_of_w;
	*len_of_w = 0;
	i = 0;
	while (**src && **src == c)
		(*src)++;
	while ((*src)[i])
	{
		if ((*src)[i] == c)
			return ;
		(*len_of_w)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char			**res;
	char			*src;
	unsigned int	len_of_w;
	unsigned int	i;

	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!res)
		return (NULL);
	i = 0;
	src = (char *)s;
	len_of_w = 0;
	while (i < word_count(s, c))
	{
		put_res(&src, &len_of_w, c);
		res[i] = (char *)malloc(sizeof(char) * (len_of_w + 1));
		if (!res)
			return (ft_malloc_error(res));
		ft_strlcpy(res[i], src, len_of_w + 1);
		i++;
	}
	res[i] = NULL;
	return (res);
}
