/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 03:07:44 by yhwang            #+#    #+#             */
/*   Updated: 2022/03/17 03:07:51 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	ft_fill_res(int len, int flag, int n, char *res)
{
	while (len > flag)
	{
		res[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*res;
	int		flag;
	int		len;

	flag = 0;
	len = get_len(n);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	if (n == -2147483648)
	{
		res[0] = '-';
		res[1] = '2';
		n = 147483648;
		flag = 2;
	}
	if (n < 0)
	{
		res[0] = '-';
		flag = 1;
		n = -n;
	}
	ft_fill_res(len, flag, n, res);
	res[len] = '\0';
	return (res);
}
