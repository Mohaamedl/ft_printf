/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:53:11 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/25 17:54:12 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>

void to_upper_with_index_even(unsigned int i, char *c) {
  if ((i + 1) % 2 == 0) {
    *c = (*c >= 'a' && *c <= 'z') ? *c - 32 : *c;
  }
}

int main() {
  char str[] = "abcdef42";

  ft_striteri(str, to_upper_with_index_even);

  printf("Modified string: %s\n", str);

  return 0;
}
*/
