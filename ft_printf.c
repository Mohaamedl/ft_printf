#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int			printed;
	t_format	f;

	printed = 0;
	va_start(ap, format);
	while(*format)
	{
		if (*format++ == '%')
		{
			f = ft_parse_format(&format, ap);
			printed += ft_conversion_handler(&format, app);
		}
		else
			printed += write(1, format,1);
	}
	va_end(ap);
	return (printed);
}
