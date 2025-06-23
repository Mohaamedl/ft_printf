/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:43:34 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/22 17:06:54 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countsize(int n);

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		nbrcpy;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	nbrcpy = n;
	if (n < 0)
		nbrcpy = -n;
	i = ft_countsize(n);
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[i--] = '\0';
	while (nbrcpy > 0)
	{
		res[i--] = nbrcpy % 10 + 48;
		nbrcpy /= 10;
	}
	if (n < 0)
		res[i] = '-';
	return (res);
}

static int	ft_countsize(int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}
/*
#include <stdio.h>
int main(void)
{
	int this = -4245232;
	char *tothis = ft_itoa(this);
	printf("result: %s", tothis);
}

*/
