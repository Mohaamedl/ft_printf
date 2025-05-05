#include "ft_printf.h"

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

