#include "ft_printf.h"

int ft_printptr(t_format *f, void *ptr)
{
    uintptr_t addr = (uintptr_t)ptr;
    char buffer[32];
    char *hex_digits = "0123456789abcdef";
    int i = 30;
    int num_len;
    int padding;
    int count = 0;

    //fprintf(stderr, "[DEBUG] Printing pointer: %p\n", ptr);
		if (ptr == NULL)
	{
		ft_printstr(f, "(nil)");
		return 5;
	}
    buffer[31] = '\0';
    if (addr == 0 && (!f->precision_specified || f->precision != 0))
        buffer[i--] = '0';
    else
    {
        while (addr > 0)
        {
            buffer[i--] = hex_digits[addr % 16];
            addr /= 16;
        }
    }
    char *num = &buffer[i + 1];
    num_len = ft_strlen(num);

    if (f->precision_specified && f->precision == 0 && ptr == 0)
        num_len = 0;

    int precision_zeros = (f->precision_specified && f->precision > num_len) ? f->precision - num_len : 0;
    int total_len = num_len + precision_zeros + 2;
    padding = (f->width > total_len) ? f->width - total_len : 0;

    if (!f->flag_minus)
        count += ft_putnchar(' ', padding);

    count += write(1, "0x", 2);
    count += ft_putnchar('0', precision_zeros);
    if (!(f->precision_specified && f->precision == 0 && ptr == 0))
        count += write(1, num, num_len);

    if (f->flag_minus)
        count += ft_putnchar(' ', padding);

    return (f->width > total_len ? f->width : total_len);
}

