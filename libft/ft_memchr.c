/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:48:54 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/26 16:49:44 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_c;
	unsigned char	c_c;
	size_t			i;

	s_c = (unsigned char *) s;
	c_c = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (s_c[i] == c_c)
			return ((void *) &s_c[i]);
		i++;
	}
	return (NULL);
}
