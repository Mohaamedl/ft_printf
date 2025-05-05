#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdint.h>

typedef struct	s_format
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

int				ft_printf(const char *format, ...);
t_format	ft_parse_format(const char **format);
int				ft_conversion_handler(t_format	*f, va_list ap);
int				ft_printchar(t_format *f, int c);
int				ft_printstr(t_format *f, char *str);
int				ft_printptr(t_format	*f, void *ptr);
int				ft_printnbr(t_format *f, int);
int				ft_printunbr(t_format *f, unsigned int);
int				ft_printhex(t_format *f, unsigned int, int uppercase);
#endif
