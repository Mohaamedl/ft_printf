/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:48:53 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/19 09:50:03 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int std_ret, ft_ret;
	char *nstr = "\0";
	char *str = "Hello";
	char c = 'A';
	void *ptr = str;
	int neg = -1234;
	int pos = 5678;
	unsigned int u = 4294967295;

	printf("\n--- Basic Tests ---\n");
	std_ret = printf("STD: Hello World\n");
	ft_ret = ft_printf("FT_: Hello World\n");
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Char ---\n");
	std_ret = printf("STD: char = %c\n", c);
	ft_ret = ft_printf("FT_: char = %c\n", c);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- String ---\n");
	std_ret = printf("STD: str = %s\n", str);
	ft_ret = ft_printf("FT_: str = %s\n", str);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Pointer ---\n");
	std_ret = printf("STD: ptr = %p\n", ptr);
	ft_ret = ft_printf("FT_: ptr = %p\n", ptr);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Integers (%%d and %%i) ---\n");
	std_ret = printf("STD: neg = %d, pos = %i\n", neg, pos);
	ft_ret = ft_printf("FT_: neg = %d, pos = %i\n", neg, pos);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Integers (%%+10d and %%+10i) ---\n");
	std_ret = printf("STD: neg = %+10.2d, pos = %+10.2i\n", neg, pos);
	ft_ret = ft_printf("FT_: neg = %+10.2d, pos = %+10.2i\n", neg, pos);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Integers (%%+09d and %%+09i) ---\n");
	std_ret = printf("STD: neg = %+09d, pos = %+09i\n", neg, pos);
	ft_ret = ft_printf("FT_: neg = %+09d, pos = %+09i\n", neg, pos);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Unsigned u---\n");
	std_ret = printf("STD:, u = %u\n", u);
	ft_ret = ft_printf("FT_:, u = %u\n", u);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Hex (lowercase) ---\n");
	std_ret = printf("STD: x = %x\n", neg);
	ft_ret = ft_printf("FT_: x = %x\n", neg);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Hex (uppercase) ---\n");
	std_ret = printf("STD: X = %X\n", neg);
	ft_ret = ft_printf("FT_: X = %X\n", neg);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Percent ---\n");
	std_ret = printf("STD: %%\n");
	ft_ret = ft_printf("FT_: %%\n");
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- NULL string and NULL pointer ---\n");
	std_ret = printf("STD: %s %p\n", nstr, NULL);
	ft_ret = ft_printf("FT_: %s %p\n", nstr, NULL);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- INT Limits ---\n");
	std_ret = printf("STD: INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
	ft_ret = ft_printf("FT_: INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	return 0;
}

