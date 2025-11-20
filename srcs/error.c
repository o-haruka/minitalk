#include <unistd.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

void print_error(const char *msg)
{
	write(1, msg, ft_strlen(msg));
    exit(1);
}
