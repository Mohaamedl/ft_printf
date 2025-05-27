/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:56:45 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/27 14:01:09 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstr(t_format *f, char *s)
{
	int	len;
	int	padding;
	int	count;

	count = 0;
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (f -> precision_specified && f -> precision < len)
		len = f->precision;
	if (f -> width > len)
		padding = f -> width - len;
	else
		padding = 0;
	if (!f->flag_minus)
		count += ft_putnchar(' ', padding);
	count += write(1, s, len);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	return (count);
}
