/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:13:46 by homura            #+#    #+#             */
/*   Updated: 2025/11/20 20:01:19 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include "../libft/includes/libft.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include <unistd.h>

static volatile sig_atomic_t	g_ack_received = 0;

static void	ack_handler(int signum)
{
	(void)signum;
	g_ack_received = 1;
}

static void	send_bit(pid_t server_pid, unsigned char bit)
{
	int	signal;

	g_ack_received = 0;
	if (bit == 0)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(server_pid, signal) == -1)
	{
		perror("kill");
		exit(EXIT_FAILURE);
	}
	while (!g_ack_received)
		usleep(50);
}

static void	send_string(pid_t server_pid, char *str)
{
	int				i;
	unsigned char	bit;
	unsigned char	c;

	i = 0;
	bit = 0;
	c = 0;
	while (1)
	{
		c = *str;
		i = 0;
		while (i < 8)
		{
			bit = (c >> i) & 1;
			send_bit(server_pid, bit);
			usleep(500);
			i++;
		}
		if (c == '\0')
			break ;
		str++;
	}
}

int	main(int argc, char **argv)
{
	int					server_pid;
	struct sigaction	sa;

	sa.sa_handler = ack_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	if (argc != 3)
		print_error("\033[31mUsage: <server_pid> <string>\033[0m\n");
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
		print_error("\033[31mInvalid server PID.\033[0m\n");
	send_string(server_pid, argv[2]);
	return (0);
}
