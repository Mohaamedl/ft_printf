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

static void	ft_ptr_to_hex(uintptr_t addr, char *buffer)
{
	char	*hex_digits;
	int		i;

	hex_digits = "0123456789abcdef";
	i = 30;
	buffer[31] = '\0';
	if (addr == 0)
		buffer[i--] = '0';
	else
	{
		while (addr > 0)
		{
			buffer[i--] = hex_digits[addr % 16];
			addr /= 16;
		}
	}
}

static int	ft_calculate_ptr_padding(t_format *f, char *num, void *ptr)
{
	int	num_len;
	int	precision_zeros;
	int	total_len;

	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && ptr == 0)
		num_len = 0;
	precision_zeros = 0;
	if (f->precision_specified && f->precision > num_len)
		precision_zeros = f->precision - num_len;
	total_len = num_len + precision_zeros + 2;
	if (f->width > total_len)
		return (f->width - total_len);
	return (0);
}

int	ft_print_ptr_content(t_format *f, char *num, void *ptr)
{
	int	count;
	int	num_len;
	int	precision_zeros;

	count = 0;
	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && ptr == 0)
		num_len = 0;
	precision_zeros = 0;
	if (f->precision_specified && f->precision > num_len)
		precision_zeros = f->precision - num_len;
	count += ft_putnchar('0', precision_zeros);
	if (!(f->precision_specified && f->precision == 0 && ptr == 0))
		count += write(1, num, num_len);
	return (count);
}

int	ft_printptr(t_format *f, void *ptr)
{
	uintptr_t	addr;
	char		buffer[32];
	char		*num;
	int			count;

	if (ptr == NULL)
		return (ft_printstr(f, "(nil)"));
	count = 0;
	addr = (uintptr_t)ptr;
	ft_ptr_to_hex(addr, buffer);
	num = &buffer[0];
	while (*num == '\0')
		num++;
	if (!f->flag_minus)
		count += ft_putnchar(' ', ft_calculate_ptr_padding(f, num, ptr));
	count += write(1, "0x", 2);
	count += ft_print_ptr_content(f, num, ptr);
	if (f->flag_minus)
		count += ft_putnchar(' ', ft_calculate_ptr_padding(f, num, ptr));
	return (count);
}

