#include "ft_printf.h"

int ft_printstr(t_format *f, char *s)
{
    int len;
    int padding;
    int count;

		count = 0;
    if (!s)
        s = "(null)";
    len = ft_strlen(s);
    if (f->precision_specified && f->precision < len)
        len = f->precision;

    padding = (f->width > len) ? f->width - len : 0;

    if (!f->flag_minus)
        count += ft_putnchar(' ', padding);
    count += write(1, s, len);
    if (f->flag_minus)
        count += ft_putnchar(' ', padding);

    return (count);
}
