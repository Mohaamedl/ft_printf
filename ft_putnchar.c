/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:55:09 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/27 13:56:31 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnchar(char c, int n)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < n)
	{
		count += write(1, &c, 1);
		i++;
	}
	return (count);
}
