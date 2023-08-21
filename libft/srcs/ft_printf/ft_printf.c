/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 02:42:02 by yhwang            #+#    #+#             */
/*   Updated: 2022/02/14 02:42:42 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_arg(char c, va_list ap, int *i)
{
	if (c == 'c')
		*i += ft_putchar(va_arg(ap, int));
	else if (c == 's')
		*i += ft_putstr(va_arg(ap, char *));
	else if (c == 'p')
	{
		ft_putstr("0x");
		*i += 2;
		*i += ft_hexa(va_arg(ap, unsigned long), 1);
	}
	else if (c == 'd' || c == 'i')
		*i += ft_putnbr(va_arg(ap, int));
	else if (c == 'u')
		*i += ft_unsigned_int(va_arg(ap, unsigned int));
	else if (c == 'x')
		*i += ft_hexa(va_arg(ap, unsigned int), 1);
	else if (c == 'X')
		*i += ft_hexa(va_arg(ap, unsigned int), 0);
	else if (c == '%')
		*i += ft_putchar('%');
	else
		*i += ft_putchar(c);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	va_list	ap;

	i = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				return (i);
			ft_print_arg(*format, ap, &i);
		}
		else
		{
			ft_putchar(*format);
			i++;
		}
		format++;
	}
	va_end(ap);
	return (i);
}
