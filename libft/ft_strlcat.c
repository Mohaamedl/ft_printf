/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:54:34 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/26 16:56:11 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	src_len;
	size_t	dest_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (n <= dest_len)
		dest_len = n;
	if (dest_len == n)
		return (dest_len + src_len);
	if ((src_len + dest_len) < n)
		ft_memcpy(dest + dest_len, src, src_len + 1);
	else
	{
		ft_memcpy(dest + dest_len, src, n - dest_len - 1);
		dest[n - 1] = '\0';
	}
	return (src_len + dest_len);
}
/*
#include <string.h>
#include <stdio.h>

int main(void)
{
    char dest[6] = "batata";
    char src[6] = "banana";
    ft_strlcat(dest,src, 12);
    printf("adding batata to banana, got : %s", dest);
}
*/
