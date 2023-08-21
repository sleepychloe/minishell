/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:52:10 by yhwang            #+#    #+#             */
/*   Updated: 2021/07/22 18:52:14 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *find, size_t length)
{
	size_t	i;
	size_t	j;

	if (find[0] == 0)
		return ((char *)src);
	i = 0;
	while (src[i] && i < length)
	{
		j = 0;
		while (src[i + j] == find[j] && i + j < length)
		{
			j++;
			if (find[j] == 0)
				return ((char *)src + i);
		}
		i++;
	}
	return (0);
}
