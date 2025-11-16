#include "../includes/ft_ctype.h"

int	ft_isstrspace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}