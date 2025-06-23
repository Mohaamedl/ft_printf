/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:57:37 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/25 18:00:12 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_c;
	unsigned char		*src_c;

	if (!dest && !src)
		return (NULL);
	if (src > dest)
		dest = ft_memcpy(dest, src, n);
	else
	{
		dest_c = (unsigned char *) dest;
		src_c = (unsigned char *) src;
		while (n--)
			dest_c[n] = src_c[n];
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int main(void) {
  char src[6] = "batata";
  char dest[6] = "yooooo";
  ft_memmove(dest, src, 6);

  printf("This is the result: %s", dest);
}
*/
