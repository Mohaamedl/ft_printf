/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:37:00 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/05 14:40:54 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printchar(t_format *f, int c)
{
	int	padding;
	int	count;

	if (f->width > 1)
		padding = f->width - 1;
	else
		padding = 0;
	count = 0;
	if (!f->flag_minus)
		count += ft_putnchar(' ', padding);
	count += write(1, &c, 1);
	if (f->flag_minus)
		count += ft_putnchar(' ', padding);
	return (count);
}
#include <stdio.h>

int main(void)
{
	t_format f;
	
	int d = ft_printchar(&f, '1');
	printf("%d", d);
}
