/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:53:20 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/27 13:54:49 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_uitoa(unsigned int n)
{
	char			buffer[11];
	int				i;
	char			*res;

	if (n == 0)
		return (ft_strdup("0"));
	buffer[10] = '\0';
	i = 9;
	while (n > 0)
	{
		buffer[i--] = (n % 10) + '0';
		n /= 10;
	}
	res = ft_strdup(&buffer[i + 1]);
	return (res);
}

/*
#include <stdio.h>

int main(void)
{
	printf("%s",ft_uitoa(988));
}
*/
