#include "ft_printf.h"

int ft_printunbr(t_format *f, unsigned int n)
{
    char *num = ft_uitoa(n);
    char *to_free = num;
    int num_len;
    int total_len;
    int precision_zeros;
    int padding;
    int count = 0;

    //fprintf(stderr, "[DEBUG] Printing uint: %u\n", n);

    if (!num)
        return (0);
    num_len = ft_strlen(num);
    if (f->precision_specified && f->precision == 0 && n == 0)
        num_len = 0;

    precision_zeros = (f->precision_specified && f->precision > num_len) ? f->precision - num_len : 0;
    total_len = num_len + precision_zeros;
    padding = (f->width > total_len) ? f->width - total_len : 0;

    if (!f->flag_minus)
    {
        if (f->flag_zero && !f->precision_specified)
            count += ft_putnchar('0', padding);
        else
            count += ft_putnchar(' ', padding);
    }

    count += ft_putnchar('0', precision_zeros);
    if (!(f->precision_specified && f->precision == 0 && n == 0))
        count += write(1, num, num_len);

    if (f->flag_minus)
        count += ft_putnchar(' ', padding);

    free(to_free);
    return (f->width > total_len ? f->width : total_len);
}

