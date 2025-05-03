#include "ft_printf.h"

int	ft_conversion_handler(t_format	*f, va_list ap)
{
	char	spec;

	spec = f -> specifier;
	if (spec == 'c')
		return (ft_printchar(f,va_arg(ap,int)));
	else if (spec == 's')
			return (ft_printstr(f,va_arg(ap, char *)));
	else if (spec == 'd' || spec == 'i')
			return (ft_printnbr(f, va_agr(ap, int)));
	else if (spec == 'p')
			return (ft_printptr(f, va_arg(ap, void *)));
	else if (spec == 'u')
			return (ft_printunbr(f, va_arg(ap, unsigned int)));
	else if (spec == 'x')
			return (ft_printhex(f, va_arg(ap, unsigned int), 0));
	else if (spec == 'X')
			return (ft_printhex(f,va_arg(ap, unsigned int), 0));
	else if (spec == '%')
			return (write(1, "%", 1));
	return (0);
}
