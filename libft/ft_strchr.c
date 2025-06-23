/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:30:15 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/26 16:31:19 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			c_c;

	c_c = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == c_c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == c_c)
		return ((char *) &s[i]);
	return (NULL);
}
