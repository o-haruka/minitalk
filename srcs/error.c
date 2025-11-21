#include <unistd.h>
#include <stdlib.h>
#include "../libft/includes/libft.h"

void print_error_exit(const char *msg)
{
	write(2, msg, ft_strlen(msg));
    exit(1);
}
