#include "ft_printf.h"

int ft_printnbr(t_format *f, int n)
{
    char    *num;
    char    *to_free;
    int     num_len;
    int     total_len;
    char    sign_char = 0;
    int     count = 0;

    //fprintf(stderr, "[DEBUG] Printing int: %d\n", n);
    num = ft_itoa(n);
    if (!num)
        return (0);
    to_free = num;
    num_len = ft_strlen(num);

    if (n < 0)
        sign_char = '-';
    else if (f->flag_plus)
        sign_char = '+';
    else if (f->flag_space)
        sign_char = ' ';

    if (n < 0)
        num++;

    if (f->precision_specified && f->precision == 0 && n == 0)
        num_len = 0;

    int precision_zeros = (f->precision_specified && f->precision > num_len) ? f->precision - num_len : 0;
    total_len = num_len + precision_zeros + (sign_char ? 1 : 0);
    int padding = (f->width > total_len) ? f->width - total_len : 0;

    if (!f->flag_minus)
    {
        if (f->flag_zero && !f->precision_specified)
        {
            if (sign_char)
                count += write(1, &sign_char, 1);
            count += ft_putnchar('0', padding);
        }
        else
        {
            count += ft_putnchar(' ', padding);
            if (sign_char)
                count += write(1, &sign_char, 1);
        }
    }
    else if (sign_char)
        count += write(1, &sign_char, 1);

    count += ft_putnchar('0', precision_zeros);

    if (!(f->precision_specified && f->precision == 0 && n == 0))
        count += write(1, num, num_len);

    if (f->flag_minus)
        count += ft_putnchar(' ', padding);

    free(to_free);
    return (f->width > total_len ? f->width : total_len);
}

