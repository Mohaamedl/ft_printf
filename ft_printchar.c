#include "ft_printf.h"

int ft_printchar(t_format *f, int c)
{
    //fprintf(stderr, "[DEBUG] Printing char: %c\n", c);
    int padding = (f->width > 1) ? f->width - 1 : 0;
    int count = 0;

    if (!f->flag_minus)
        count += ft_putnchar(' ', padding);
    count += write(1, &c, 1);
    if (f->flag_minus)
        count += ft_putnchar(' ', padding);
    return (count);
}
