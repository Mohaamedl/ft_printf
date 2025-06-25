/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:43:06 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/25 19:58:22 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_hex_digits(int uppercase, int n, char *buffer, int *len)
{
	char	*hex_digits;

	if (uppercase)
		hex_digits = "0123456789ABCDEF";
	else
		hex_digits = "0123456789abcdef";
	if (n == 0)
	{
		buffer[0] = '0';
		buffer[1] = '\0';
		return (" ");
	}
	*len = 0;
	return (hex_digits);
}

void	ft_hex_to_buffer(unsigned int n, char *buffer, int uppercase)
{
	char			*hex_digits;
	int				len;
	int				i;
	unsigned int	temp;

	hex_digits = ft_hex_digits(uppercase, n, buffer, &len);
	if (*hex_digits == ' ')
		return ;
	temp = n;
	while (temp > 0)
	{
		len++;
		temp /= 16;
	}
	buffer[len] = '\0';
	i = len - 1;
	while (n > 0)
	{
		buffer[i] = hex_digits[n % 16];
		n /= 16;
		i--;
	}
}
