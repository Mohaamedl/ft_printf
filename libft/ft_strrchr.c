/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:32:38 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/22 16:33:18 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			*res;
	char			c_c;

	c_c = (char) c;
	i = 0;
	res = NULL;
	while (s[i])
	{
		if (s[i] == c_c)
			res = (char *) &s[i];
		i++;
	}
	if (s[i] == c_c)
		res = (char *) &s[i];
	return (res);
}
