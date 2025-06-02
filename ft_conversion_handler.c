/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conversion_handler.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:23:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/05 14:29:47 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_conversion_handler(t_format *f, va_list ap)
{
	if (f->specifier == 'c')
        return (ft_printchar(f, va_arg(ap, int)));
	else if (f->specifier == 's')
		return (ft_printstr(f, va_arg(ap, char *)));
	else if (f->specifier == 'p')
		return (ft_printptr(f, va_arg(ap, void *)));
	else if (f->specifier == 'd' || f->specifier == 'i')
		return (ft_printnbr(f, va_arg(ap, int)));
	else if (f->specifier == 'u')
		return (ft_printunbr(f, va_arg(ap, unsigned int)));
	else if (f->specifier == 'x')
		return (ft_printhex(f, va_arg(ap, unsigned int), 0));
	else if (f->specifier == 'X')
		return (ft_printhex(f, va_arg(ap, unsigned int), 1));
	else if (f->specifier == '%')
		return (ft_printchar(f, '%'));
	return (0);
}
