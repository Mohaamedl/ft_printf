/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname <yourname@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:00:00 by yourname          #+#    #+#             */
/*   Updated: 2025/05/01 00:00:00 by yourname         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h> // For debugging output

int ft_printf(const char *format, ...)
{
    va_list ap;
    int     printed;

    printed = 0;
    va_start(ap, format);
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            t_format f = ft_parse_format(&format);
            printed += ft_conversion_handler(&f, ap);
        }
        else
            printed += write(1, format++, 1);
    }
    va_end(ap);
    return (printed);
}

/* ************************************************************************** */
/*                                                                            */
/*                              parse_format.c                                */
/*                                                                            */
/* ************************************************************************** */


static int is_flag(char c)
{
    return (c == '-' || c == '0' || c == '.' || c == '#' || c == '+' || c == ' ');
}

static int is_specifier(char c)
{
    return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u'
            || c == 'x' || c == 'X' || c == '%');
}

t_format ft_parse_format(const char **format)
{
    t_format f;
	char **fmt = (char **)format;

    ft_bzero(&f, sizeof(t_format));
    while (is_flag(**fmt))
    {
        if (**fmt == '-') f.flag_minus = 1;
        if (**fmt == '0') f.flag_zero = 1;
        if (**fmt == '#') f.flag_hash = 1;
        if (**fmt == '+') f.flag_plus = 1;
        if (**fmt == ' ') f.flag_space = 1;
        (*fmt)++;
    }
    if (ft_isdigit(**fmt))
    {
        f.width = ft_atoi(*fmt);
        while (ft_isdigit(**fmt))
            (*fmt)++;
    }
    if (**fmt == '.')
    {
        f.precision_specified = 1;
        (*fmt)++;
        f.precision = ft_atoi(*fmt);
        while (ft_isdigit(**fmt))
            (*fmt)++;
    }
    if (is_specifier(**fmt))
        f.specifier = *(*fmt)++;
    return (f);
}

/* ************************************************************************** */
/*                            handle_conversion.c                             */
/* ************************************************************************** */



int ft_conversion_handler(t_format *f, va_list ap)
{
	if (f->specifier == 'c')
        return (ft_printchar(f, va_arg(ap, int)));
    else if (f->specifier == 's')
        return (ft_printstr(f, va_arg(ap, char *)));
    else if (f->specifier == 'p')
        return (ft_printptr(f, va_arg(ap, void *)));
    else if (f->specifier == 'd' || f->specifier == 'i')
        return (ft_printnbr(f, va_arg(ap, int)));
    else if (f->specifier == 'u')
        return (ft_printunbr(f, va_arg(ap, unsigned int)));
    else if (f->specifier == 'x')
        return (ft_printhex(f, va_arg(ap, unsigned int), 0));
    else if (f->specifier == 'X')
        return (ft_printhex(f, va_arg(ap, unsigned int), 1));
    else if (f->specifier == '%')
        return (ft_printchar(f, '%'));
    return (0);
}

/* ************************************************************************** */
/*                           print_utils_bonus.c                              */
/* ************************************************************************** */

char	*ft_uitoa(unsigned int n)
{
	char			buffer[11]; // Max 10 digits + '\0'
	int				i;
	char			*res;

	if (n == 0)
		return (ft_strdup("0"));
	buffer[10] = '\0';
	i = 9;
	while (n > 0)
	{
		buffer[i--] = (n % 10) + '0';
		n /= 10;
	}
	res = ft_strdup(&buffer[i + 1]);
	return (res);
}


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

int ft_printstr(t_format *f, char *s)
{
    int len;
    int padding;
    int count = 0;

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
	//printf("number: %s", num);
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
        count += write(1, num, ft_strlen(num));
    if (f->flag_minus)
        count += ft_putnchar(' ', padding);
    free(to_free);
    return (count);
}


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
    return (count);
}

int ft_printhex(t_format *f, unsigned int n, int uppercase)
{
    char *hex_digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
    char buffer[32];
    int i = 30;
    int num_len;
    int total_len;
    int precision_zeros;
    int padding;
    int count = 0;

    //fprintf(stderr, "[DEBUG] Printing hex: %x, uppercase=%d\n", n, uppercase);

    buffer[31] = '\0';
    if (n == 0 && (!f->precision_specified || f->precision != 0))
        buffer[i--] = '0';
    else if (n != 0 || (f->precision_specified && f->precision != 0))
    {
        unsigned int tmp = n;
        while (tmp > 0)
        {
            buffer[i--] = hex_digits[tmp % 16];
            tmp /= 16;
        }
    }
    char *num = &buffer[i + 1];
    num_len = ft_strlen(num);
    if (f->precision_specified && f->precision == 0 && n == 0)
        num_len = 0;

    precision_zeros = (f->precision_specified && f->precision > num_len) ? f->precision - num_len : 0;
    total_len = num_len + precision_zeros;
    if (f->flag_hash && n != 0)
        total_len += 2;
    padding = (f->width > total_len) ? f->width - total_len : 0;

    if (!f->flag_minus)
    {
        if (f->flag_zero && !f->precision_specified)
        {
            if (f->flag_hash && n != 0)
                count += write(1, uppercase ? "0X" : "0x", 2);
            count += ft_putnchar('0', padding);
        }
        else
        {
            count += ft_putnchar(' ', padding);
            if (f->flag_hash && n != 0)
                count += write(1, uppercase ? "0X" : "0x", 2);
        }
    }
    else if (f->flag_hash && n != 0)
        count += write(1, uppercase ? "0X" : "0x", 2);

    count += ft_putnchar('0', precision_zeros);
    if (!(f->precision_specified && f->precision == 0 && n == 0))
        count += write(1, num, num_len);

    if (f->flag_minus)
        count += ft_putnchar(' ', padding);

    return (count);
}

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

    return (count);
}

#include <limits.h>

int main(void)
{
	int std_ret, ft_ret;
	char *nstr = "\0";
	char *str = "Hello";
	char c = 'A';
	void *ptr = str;
	int neg = -1234;
	int pos = 5678;
	unsigned int u = 4294967295;

	printf("\n--- Basic Tests ---\n");
	std_ret = printf("STD: Hello World\n");
	ft_ret = ft_printf("FT_: Hello World\n");
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Char ---\n");
	std_ret = printf("STD: char = %c\n", c);
	ft_ret = ft_printf("FT_: char = %c\n", c);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- String ---\n");
	std_ret = printf("STD: str = %s\n", str);
	ft_ret = ft_printf("FT_: str = %s\n", str);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Pointer ---\n");
	std_ret = printf("STD: ptr = %p\n", ptr);
	ft_ret = ft_printf("FT_: ptr = %p\n", ptr);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Integers (%%d and %%i) ---\n");
	std_ret = printf("STD: neg = %d, pos = %i\n", neg, pos);
	ft_ret = ft_printf("FT_: neg = %d, pos = %i\n", neg, pos);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Integers (%%+9d and %%+9i) ---\n");
	std_ret = printf("STD: neg = %+9d, pos = %+9i\n", neg, pos);
	ft_ret = ft_printf("FT_: neg = %+9d, pos = %+9i\n", neg, pos);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);


	printf("\n--- Unsigned ---\n");
	std_ret = printf("STD:, u = %u\n", u);
	ft_ret = ft_printf("FT_:, u = %u\n", u);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Hex (lowercase) ---\n");
	std_ret = printf("STD: x = %x\n", neg);
	ft_ret = ft_printf("FT_: x = %x\n", neg);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Hex (uppercase) ---\n");
	std_ret = printf("STD: X = %X\n", neg);
	ft_ret = ft_printf("FT_: X = %X\n", neg);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- Percent ---\n");
	std_ret = printf("STD: %%\n");
	ft_ret = ft_printf("FT_: %%\n");
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- NULL string and NULL pointer ---\n");
	std_ret = printf("STD: %s %p\n", nstr, NULL);
	ft_ret = ft_printf("FT_: %s %p\n", nstr, NULL);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);

	printf("\n--- INT Limits ---\n");
	std_ret = printf("STD: INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
	ft_ret = ft_printf("FT_: INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
	printf("Return: std = %d, ft = %d\n", std_ret, ft_ret);
	int r1 = printf("std:%+#0.-\n",42);
	printf("r: %d", r1);
	int r2 = ft_printf("ft:%+#0.-\n",42);
	printf("r: %d", r2);


	return 0;
}
