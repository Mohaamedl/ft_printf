#include "ft_printf.h"

int ft_printpercent(t_format *f)
{
    int padding = (f->width > 1) ? f->width - 1 : 0;
    int count = 0;

    if (!f->flag_minus)
        count += ft_putnchar(f->flag_zero ? '0' : ' ', padding);
    count += write(1, "%", 1);
    if (f->flag_minus)
        count += ft_putnchar(' ', padding);
    return (count);
}
