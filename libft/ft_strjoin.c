/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:36:49 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/22 16:39:35 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
		while (s1[i])
			str[j++] = s1[i++];
	i = 0;
	if (s2)
		while (s2[i])
			str[j++] = s2[i++];
	str[j] = 0;
	return (str);
}
/*
#include <stdio.h>

int main(void) {
  char *joined = ft_strjoin("42", " here");
  if (joined) {
    printf("%s\n", joined);
    free(joined);
  }

  char *only = ft_strjoin(NULL, "42");
  if (only) {
    printf("%s\n", only);
    free(only);
  }

  char *none = ft_strjoin(NULL, NULL);
  if (!none)
    printf("NULL correctly returned\n");

  return 0;
}
*/
