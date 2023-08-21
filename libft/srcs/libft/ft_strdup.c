/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 23:02:55 by yhwang            #+#    #+#             */
/*   Updated: 2021/07/22 23:10:26 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	len;

	if (src == NULL)
		return (NULL);
	len = 0;
	while (src[len])
		len++;
	dup = (char *)malloc(len + 1);
	if (!(dup))
		return (NULL);
	ft_memcpy(dup, src, len);
	dup[len] = 0;
	return (dup);
}
