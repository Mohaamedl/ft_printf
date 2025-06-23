/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:10:09 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/14 17:11:42 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp;

	temp = (char *) s;
	while (n > 0)
	{
		*(temp++) = 0;
		n--;
	}
}
/*
#include <stdio.h>
int main(void)
{
	char test[11];
		
	snprintf(test, sizeof(test), "DDDDDDDDDD");

	ft_bzero(test, 5);
	//unsigned char *temp = (unsigned char *) test;
	printf("This is the output: %s and this is the sp
	ected value: DD",(char*) test);
}
*/
