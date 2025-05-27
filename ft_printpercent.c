/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpercent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:01:47 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/27 14:07:54 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printpercent(t_format *f)
{
	int	padding;
	int	count;

	if (f -> width > 1)
		padding = f -> width - 1;
	else
		padding = 0;
	count = 0;
	if (!f->flag_minus)
	{
		if (f -> flag_zero)
			count += ft_putnchar('0', padding);
		else
			count += ft_putnchar(' ', padding);
	}
	count += write(1, "%", 1);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	return (count);
}
