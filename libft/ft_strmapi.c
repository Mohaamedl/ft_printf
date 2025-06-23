/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:26:30 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/26 16:28:41 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*res;

	if (!s || !f)
		return (NULL);
	res = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
/*
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char to_upper_with_index(unsigned int i, char c) {
  (void)i;
  return toupper((unsigned char)c);
}

int main(void) {
  const char *original = "hello42";
  char *mapped = ft_strmapi(original, to_upper_with_index);

  if (mapped) {
    printf("Original: %s\n", original);
    printf("Mapped  : %s\n", mapped);
    free(mapped);
  } else {
    printf("Error allocating memory\n");
  }

  return 0;
}*/
