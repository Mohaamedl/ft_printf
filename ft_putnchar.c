#include "ft_printf.h"

int ft_putnchar(char c, int n)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (i < n)
    {
        count += write(1, &c, 1);
        i++;
    }
    return (count);
}
