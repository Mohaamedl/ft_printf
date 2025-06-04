/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:23:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/05 14:29:47 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_unsigned_padding(t_format *f, int padding);
static int	print_unsigned_with_format(t_format *f, char *num, int num_len,
				unsigned int n);

int	ft_printunbr(t_format *f, unsigned int n)
{
	char	*num;
	char	*to_free;
	int		num_len;
	int		count;

	num = ft_uitoa(n);
	if (!num)
		return (0);
	to_free = num;
	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && n == 0)
		num_len = 0;
	count = print_unsigned_with_format(f, num, num_len, n);
	free(to_free);
	return (count);
}

static int	print_unsigned_with_format(t_format *f, char *num, int num_len,
	unsigned int n)
{
	int	count;
	int	precision_zeros;
	int	total_len;
	int	padding;

	count = 0;
	if (f->precision_specified && f->precision > num_len)
		precision_zeros = f->precision - num_len;
	else
		precision_zeros = 0;
	total_len = num_len + precision_zeros;
	if (f->width > total_len)
		padding = f->width - total_len;
	else
		padding = 0;
	count += handle_unsigned_padding(f, padding);
	count += ft_putnchar('0', precision_zeros);
	if (!(f->precision_specified && f->precision == 0 && n == 0))
		count += write(1, num, num_len);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	return (count);
}

static int	handle_unsigned_padding(t_format *f, int padding)
{
	if (!f->flag_minus)
	{
		if (f->flag_zero && !f->precision_specified)
			return (ft_putnchar('0', padding));
		else
			return (ft_putnchar(' ', padding));
	}
	return (0);
}
