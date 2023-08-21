/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:47:04 by yhwang            #+#    #+#             */
/*   Updated: 2021/07/22 18:47:07 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t length)
{
	unsigned char	*usrc;
	unsigned char	*udst;

	if (dst == src || length == 0)
		return (dst);
	if (dst < src)
	{
		udst = (unsigned char *)dst;
		usrc = (unsigned char *)src;
		while (length--)
			*udst++ = *usrc++;
	}
	else
	{
		udst = (unsigned char *)dst + (length - 1);
		usrc = (unsigned char *)src + (length - 1);
		while (length--)
			*udst-- = *usrc--;
	}
	return (dst);
}
