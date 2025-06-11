/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 13:59:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/11 14:04:02 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
	int	ft;
	int	std;
	int	pos;
	int	neg;
	unsigned int uint;
	char	*str;


	pos = 1010;
	neg = -1010;
	uint = 4009990999;
	str = "testing string printing";
	printf("Integers\n");
	std = printf("std: %d\n",pos);
	ft = ft_printf("ft : %d\n",pos);
	printf("Returns----\nft: %10d\nstd: %10d\n", std, ft);
	

	printf("Unsigned ints\n");
	std = printf("std: %u\n",uint);
	ft	= ft_printf("ft : %u\n",uint);
	printf("Returns----\nft: %10d\nstd: %10d\n", std, ft);
	

	printf("Strings\n");
	std = printf("std: %s\n", str);
	ft	= ft_printf("ft : %s\n", str);
	printf("Returns----\nft: %10d\nstd: %10d\n", std, ft);
	
	printf("Hexa X\n");
	std = printf("std: %X\n", neg);
	ft	= ft_printf("ft : %X\n", neg);
	printf("Returns----\nft: %10d\nstd: %10d\n", std, ft);

	printf("-----------Testing combination flags---------\n");
	printf("testing \n");
	

}
