/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:43:54 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/27 13:47:31 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printhex(t_format *f, unsigned int n, int uppercase)
{
    char *hex_digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    char buffer[32];
    int i = 30;
    int num_len;
    int total_len;
    int precision_zeros;
    int padding;
    int count = 0;

    buffer[31] = '\0';
    if (n == 0 && (!f->precision_specified || f->precision != 0))
        buffer[i--] = '0';
    else if (n != 0 || (f->precision_specified && f->precision != 0))
    {
        unsigned int tmp = n;
        while (tmp > 0)
        {
            buffer[i--] = hex_digits[tmp % 16];
            tmp /= 16;
        }
    }
    char *num = &buffer[i + 1];
    num_len = ft_strlen(num);
    if (f->precision_specified && f->precision == 0 && n == 0)
        num_len = 0;

    precision_zeros = (f->precision_specified && f->precision > num_len) ? f->precision - num_len : 0;
    total_len = num_len + precision_zeros;
    if (f->flag_hash && n != 0)
        total_len += 2;
    padding = (f->width > total_len) ? f->width - total_len : 0;

    if (!f->flag_minus)
    {
        if (f->flag_zero && !f->precision_specified)
        {
            if (f->flag_hash && n != 0)
                count += write(1, uppercase ? "0X" : "0x", 2);
            count += ft_putnchar('0', padding);
        }
        else
        {
            count += ft_putnchar(' ', padding);
            if (f->flag_hash && n != 0)
                count += write(1, uppercase ? "0X" : "0x", 2);
        }
    }
    else if (f->flag_hash && n != 0)
        count += write(1, uppercase ? "0X" : "0x", 2);

    count += ft_putnchar('0', precision_zeros);
    if (!(f->precision_specified && f->precision == 0 && n == 0))
        count += write(1, num, num_len);

    if (f->flag_minus)
        count += ft_putnchar(' ', padding);

    return (count);
}

