#include "ft_printf.h"

static int	is_frag(char c)
{
	return (c == '-' || c == '0' || c == 'p' || c == '#' || c == '+' || c == ' ');
}
static int	is_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'd' || c == 'p' || c == 'i' || c == 'u'
				  || c == 'x' || c == 'X' || c == '%');
}

t_format	ft_parse_format(const char **format)
{
	t_format f;

	ft_bzero(&f, sizeof(t_format));
	while(is_flag(**format))
	{
		if (**format == '-')
			f.flag_minus = 1;
		if (**format == '0')
			f.flag_zero = 1;
		if (**format == '#')
			f.flag_hash = 1;
		if (**format == '+')
			f.flag_plus = 1;
		if (**format == ' ')
			f.flag_space = 1;
		(*format)++;
	}
	if (ft_isdigit(**format))
	{
		f.width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	if (**format == '.')
	{
		f.precision_specified = 1;
		(*format)++;
		f.precision = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
	}
	if (is_specifier(**format))
		f.specifier = *(*format)++;
	return (f);
}
