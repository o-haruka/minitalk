#include "../include/minitalk.h"
#include "../libft/includes/libft.h"

static int	client_error_msg(void)
{
	ft_putendl_fd("\033[31mError", 2);
	ft_putendl_fd(" Usage: ./client [PID] [message]\033[0m", 2);
	return (1);
}

static int	send_error(void)
{
	ft_putendl_fd("\033[31mError", 2);
	ft_putendl_fd(" Failed to send signal (invalid PID?)\033[0m", 2);
	return (1);
}

static int	send_char(int pid, char str)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((str & (1 << i)) != 0)
		{
			if (kill(pid, SIGUSR1) == -1)
				return (-1);
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				return (-1);
		}
		usleep(500);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	i = 0;
	if (argc != 3)
		return (client_error_msg());
	while (argv[1][i] != '\0')
	{
		if (!ft_isdigit(argv[1][i++]))
			return (client_error_msg());
	}
	i = 0;
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
		return (client_error_msg());
	while (argv[2][i] != '\0')
	{
		if (send_char(pid, argv[2][i++]) == -1)
			return (send_error());
	}
	if (send_char(pid, '\n') == -1)
		return (send_error());
	return (0);
}