/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddadi <mhaddadi@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 10:27:06 by mhaddadi          #+#    #+#             */
/*   Updated: 2025/06/25 19:58:34 by mhaddadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* ************************************************************************** */
/*                                    Some LIBS                               */
/* ************************************************************************** */
# include "../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>

/* ************************************************************************** */
/*                                    Structs                               */
/* ************************************************************************** */

typedef struct s_format
{
	int		flag_minus;
	int		flag_zero;
	int		flag_hash;
	int		flag_plus;
	int		flag_space;
	int		width;
	int		precision_specified;
	int		precision;
	char	specifier;
}				t_format;

/* ************************************************************************** */
/*                                    Functions                               */
/* ************************************************************************** */

int				ft_printf(const char *format, ...);
t_format		ft_parse_format(const char **format);
int				ft_conversion_handler(t_format *f, va_list ap);
int				ft_printchar(t_format *f, int c);
int				ft_printstr(t_format *f, char *str);
int				ft_printptr(t_format *f, void *ptr);
int				ft_printnbr(t_format *f, int n);
int				ft_printunbr(t_format *f, unsigned int n);
int				ft_printhex(t_format *f, unsigned int n, int uppercase);
int				ft_printpercent(t_format *f);
int				ft_putnchar(char c, int num);
char			*ft_uitoa(unsigned int n);
int				ft_calculate_hex_padding(t_format *f, char *num,
					unsigned int n);
int				ft_print_ptr_content(t_format *f, char *num, void *ptr);
void			ft_hex_to_buffer(unsigned int n, char *buffer, int uppercase);

#endif
