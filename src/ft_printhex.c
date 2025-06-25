/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:43:54 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/25 19:59:30 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_hex_prefix(t_format *f, unsigned int n, int uppercase)
{
	int	count;

	count = 0;
	if (f->flag_hash && n != 0)
	{
		if (uppercase)
			count += write(1, "0X", 2);
		else
			count += write(1, "0x", 2);
	}
	return (count);
}

static int	ft_print_hex_content(t_format *f, char *num, unsigned int n)
{
	int	count;
	int	num_len;
	int	precision_zeros;

	count = 0;
	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && n == 0)
		num_len = 0;
	precision_zeros = 0;
	if (f->precision_specified && f->precision > num_len)
		precision_zeros = f->precision - num_len;
	count += ft_putnchar('0', precision_zeros);
	if (!(f->precision_specified && f->precision == 0 && n == 0))
		count += write(1, num, num_len);
	return (count);
}

int	ft_calculate_hex_padding(t_format *f, char *num, unsigned int n)
{
	int	num_len;
	int	precision_zeros;
	int	total_len;

	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && n == 0)
		num_len = 0;
	precision_zeros = 0;
	if (f->precision_specified && f->precision > num_len)
		precision_zeros = f->precision - num_len;
	total_len = num_len + precision_zeros;
	if (f->flag_hash && n != 0)
		total_len += 2;
	if (f->width > total_len)
		return (f->width - total_len);
	return (0);
}

int	ft_printhex(t_format *f, unsigned int n, int uppercase)
{
	char	buffer[32];
	char	*num;
	int		count;
	int		padding;

	count = 0;
	ft_hex_to_buffer(n, buffer, uppercase);
	num = buffer;
	padding = ft_calculate_hex_padding(f, num, n);
	if (!f->flag_minus)
	{
		if (f->flag_zero && !f->precision_specified)
		{
			count += ft_print_hex_prefix(f, n, uppercase);
			count += ft_putnchar('0', padding);
		}
		else
			count += ft_putnchar(' ', padding);
	}
	if (!f->flag_zero || f->precision_specified)
		count += ft_print_hex_prefix(f, n, uppercase);
	count += ft_print_hex_content(f, num, n);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	return (count);
}
