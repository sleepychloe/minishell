/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 18:43:54 by yhwang            #+#    #+#             */
/*   Updated: 2021/07/22 18:43:57 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t num)
{
	while (num--)
	{
		if (*(unsigned char *)ptr == (unsigned char)value)
			return ((void *)ptr);
		ptr++;
	}
	return (0);
}
