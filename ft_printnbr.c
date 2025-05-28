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

static void	ft_sign(int n, char *sign_char, char *num, t_format *f, int count)
{
	sign_char = 0;
	count = 0;
	if (n < 0)
	{
		*sign_char = '-';
		num++;
	}
	else if (f -> flag_plus)
		*sign_char = '+';
	else if (f -> flag_space)
		*sign_char = ' ';
}

static void	ft_print_signs(char *sign_char, int padding,
						   int  precision_zeros, int *count, t_format *f)
{
	if (!f -> flag_minus)
	{
		if (f -> flag_zero && !f -> precision_specified)
		{
			if (sign_char)
				*count += write(1, &sign_char, 1);
			*count += ft_putnchar('0', padding);
		}
		else
		{
			*count += ft_putnchar(' ', padding);
			if (sign_char)
				*count += write(1, &sign_char, 1);
		}
	}
	else if (sign_char)
		*count += write(1, &sign_char, 1);
	*count += ft_putnchar('0', precision_zeros);
}

int	ft_printnbr(t_format *f, int n)
{
	char	*num;
	char	*to_free;
	int		num_len;
	int		total_len;
	char	sign_char;
	int		count;
	int		precision_zeros;

	num = ft_itoa(n);
	if (!num)
		return (0);
	ft_sign(n, &sign_char, num, f, count);
	to_free = num;
	num_len = ft_strlen(num);
	if (f->precision_specified && f->precision == 0 && n == 0)
		num_len = 0;
	if (f->precision_specified && f->precision > num_len)
		precision_zeros = f->precision - num_len;
	else
		precision_zeros = 0;
		
	//int precision_zeros = (f->precision_specified && f->precision > num_len) ? f->precision - num_len : 0;
	
	total_len = num_len + precision_zeros + (sign_char ? 1 : 0);
	int padding = (f->width > total_len) ? f->width - total_len : 0;
	if (!(f->precision_specified && f->precision == 0 && n == 0))
	    count += write(1, num, num_len);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	free(to_free);
	return (count);
}
void ft_padding(t_format *f, int *padding, int *num_len, int *n)
{
	int		total_len;
	int		precision_zeros;
	if (f->precision_specified && f->precision == 0 && *n == 0)
		*num_len = 0;
	if (f->precision_specified && f->precision > *num_len)
		precision_zeros = f->precision - *num_len;
	else
		precision_zeros = 0;
	if (sign_char)
		total_len = num_len + precision
}











