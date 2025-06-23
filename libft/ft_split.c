/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:51:07 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/04/22 15:54:06 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_init(size_t *i, size_t *j, int *word_s);

static int	ft_wcount(char const *s, char c);

static char	*ft_strfill(const char *str, size_t start, size_t end);

static void	*ft_free(char **str, size_t count);

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	i;
	size_t	j;
	int		start;

	ft_init(&i, &j, &start);
	words = ft_calloc(ft_wcount(s, c) + 1, sizeof(char *));
	if (!words)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			words[j] = ft_strfill(s, start, i);
			if (!words[j])
				return (ft_free(words, j));
			start = -1;
			j++;
		}
		i++;
	}
	return (words);
}

static void	ft_init(size_t *i, size_t *j, int *word_s)
{
	*i = 0;
	*j = 0;
	*word_s = -1;
}

static int	ft_wcount(char const *s, char c)
{
	size_t	i;
	size_t	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	while (*s)
	{
		if (*s != c && i == 0)
		{
			i = 1;
			count++;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (count);
}

static char	*ft_strfill(const char *str, size_t start, size_t end)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc((end - start + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (start < end)
	{
		res[i] = str[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

static void	*ft_free(char **str, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(str[i++]);
	}
	free(str);
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main(void)
{
        char	*phrase = "44batata4this4is 4 batata 4444 gggg4";
        char	delimiter = '4';
        int	wcount = ft_wcount(phrase,delimiter);
        //char *words[];

        //char *words[] = {"aaa", "bbb", "cccc"};
        words = ft_split(phrase, delimiter);

        int	i =0;
        while (*words[i])
        {

                printf("%s\n", words[i++]);
        }
        printf("the word: %s \n has %d words separated by %c",
        phrase, wcount, delimiter);
        return (0);
}
*/
