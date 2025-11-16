#include "../includes/ft_ctype.h"

int	ft_isspace(int c)
{
	return ((c == ' ') || (9 <= c && c <= 13));
}