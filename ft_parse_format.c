/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:23:22 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/05/05 14:29:47 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	is_flag(char c)
{
	return (c == '-' || c == '0' || c == '#' || c == '+' || c == ' ');
}

static int	is_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
		|| c == 'x' || c == 'X' || c == '%');
}

static void	parse_fmt(t_format *f, const char **fmt)
{
	while (is_flag(**fmt))
	{
		if (**fmt == '-')
			f->flag_minus = 1;
		if (**fmt == '0')
			f->flag_zero = 1;
		if (**fmt == '#')
			f->flag_hash = 1;
		if (**fmt == '+')
			f->flag_plus = 1;
		if (**fmt == ' ')
			f->flag_space = 1;
		(*fmt)++;
	}
}

t_format	ft_parse_format(const char **format)
{
	t_format	f;
	char		**fmt;

	fmt = (char **)format;
	ft_bzero(&f, sizeof(t_format));
	parse_fmt(&f, format);
	if (ft_isdigit(**fmt))
	{
		f.width = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
	if (**fmt == '.')
	{
		f.precision_specified = 1;
		(*fmt)++;
		f.precision = ft_atoi(*fmt);
		while (ft_isdigit(**fmt))
			(*fmt)++;
	}
	if (is_specifier(**fmt))
		f.specifier = *(*fmt)++;
	return (f);
}
