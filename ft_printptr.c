/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:45:01 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/05 15:47:41 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printptr(t_format *f, void *ptr)
{
	uintptr_t	addr;
	char		buffer[32];
	char		*hex_digits;
	int			i;
	size_t		num_len;
	int			padding;
	int			count;
	char		*num;

	count = 0;
	hex_digits = "0123456789abcdef";
	addr = (uintptr_t) ptr;
	if (ptr == NULL)
	{
		ft_printstr(f, "(nil)");
		return 5;
	}
	buffer[31] = '\0';
	if (addr == 0 && (!f->precision_specified || f->precision != 0))
		buffer[i--] = '0';
	else
	{
		while (addr > 0)
		{
			buffer[i--] = hex_digits[addr % 16];
			addr /= 16;
		}
	}
	num = &buffer[i + 1];
	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && ptr == 0)
		num_len = 0;
	int precision_zeros = (f->precision_specified && f->precision > num_len) ? f->precision - num_len : 0;
	int total_len = num_len + precision_zeros + 2;
	padding = (f->width > total_len) ? f->width - total_len : 0;
	if (!f->flag_minus)
		count += ft_putnchar(' ', padding);
	count += write(1, "0x", 2);
	count += ft_putnchar('0', precision_zeros);
	if (!(f->precision_specified && f->precision == 0 && ptr == 0))
		count += write(1, num, num_len);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	return (f->width > total_len ? f->width : total_len);
}

