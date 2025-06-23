/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:57:41 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/26 16:58:59 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char						*dest_c;
	unsigned char						*src_c;
	size_t								i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dest_c = (unsigned char *) dest;
	src_c = (unsigned char *) src;
	while (i < n)
	{
		dest_c[i] = src_c[i];
		i++;
	}
	return (dest_c);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char src[] = "Hello, world!";
  char dest1[50];
  char dest2[50];

  // Use ft_memcpy
  ft_memcpy(dest1, src, strlen(src) + 1); // +1 to copy the null terminator

  // Use standard memcpy for comparison
  memcpy(dest2, src, strlen(src) + 1);

  // Print results
  printf("Source     : %s\n", src);
  printf("ft_memcpy  : %s\n", dest1);
  printf("memcpy     : %s\n", dest2);

  // Check if both results are equal
  if (strcmp(dest1, dest2) == 0)
    printf("Test passed: ft_memcpy behaves like memcpy.\n");
  else
    printf("Test failed: ft_memcpy differs from memcpy.\n");

  return 0;
}

*/
