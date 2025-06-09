/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:44:50 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/27 14:23:13 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	get_sign_char(t_format *f, int n);
static int	print_number_content(t_format *f, char *num, int num_len, int n);
static int	print_number_with_format(t_format *f, char *num, int num_len,
				int n);
static int	calculate_total_width(t_format *f, int num_len, char sign_char);

static char	get_sign_char(t_format *f, int n)
{
	if (n < 0)
		return ('-');
	else if (f->flag_plus)
		return ('+');
	else if (f->flag_space)
		return (' ');
	return (0);
}

static int	print_number_content(t_format *f, char *num, int num_len, int n)
{
	int	count;
	int	precision_zeros;

	count = 0;
	if (f->precision_specified && f->precision > num_len)
		precision_zeros = f->precision - num_len;
	else
		precision_zeros = 0;
	count += ft_putnchar('0', precision_zeros);
	if (!(f->precision_specified && f->precision == 0 && n == 0))
		count += write(1, num, num_len);
	return (count);
}

static int	calculate_total_width(t_format *f, int num_len, char sign_char)
{
	int	total_width;

	total_width = num_len;
	if (sign_char)
		total_width++;
	if (f->precision_specified && f->precision > num_len)
	{
		if (sign_char)
			total_width = f->precision + 1;
		else
			total_width = f->precision;
	}
	return (total_width);
}

static int	print_number_with_format(t_format *f, char *num, int num_len, int n)
{
	int		count;
	int		padding;
	char	sign_char;

	count = 0;
	sign_char = get_sign_char(f, n);
	if (f->width > calculate_total_width(f, num_len, sign_char))
		padding = f->width - calculate_total_width(f, num_len, sign_char);
	else
		padding = 0;
	
	// When precision is specified, always use space padding
	if (!f->flag_minus && (f->precision_specified || !f->flag_zero))
		count += ft_putnchar(' ', padding);
	
	if (sign_char)
		count += write(1, &sign_char, 1);
	
	// Only use zero padding when no precision is specified and zero flag is set
	if (!f->flag_minus && f->flag_zero && !f->precision_specified)
		count += ft_putnchar('0', padding);
	
	count += print_number_content(f, num, num_len, n);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	return (count);
}

int	ft_printnbr(t_format *f, int n)
{
	char	*num;
	char	*to_free;
	int		num_len;
	int		count;

	num = ft_itoa(n);
	if (!num)
		return (0);
	to_free = num;
	num_len = ft_strlen(num);
	if (n < 0)
	{
		num++;
		num_len--;
	}
	if (f->precision_specified && f->precision == 0 && n == 0)
		num_len = 0;
	count = print_number_with_format(f, num, num_len, n);
	free(to_free);
	return (count);
}
