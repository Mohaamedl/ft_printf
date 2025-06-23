/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:14:09 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/14 16:43:25 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *) s;
	while (n > 0)
	{
		*(temp++) = (unsigned char) c;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>
int main(void)
{
	void *test[10];
	
	
	// test = "dsdsdsd";
	void *result;
	result = ft_memset(test, 67, 8);
	//unsigned char *temp = (unsigned char *) test;
	printf("This is the output: %s and this is the spected value: 
	CCCCCCCC",(unsigned char*) result);
}
*/
