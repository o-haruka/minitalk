/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:13:46 by homura            #+#    #+#             */
/*   Updated: 2025/11/16 20:17:15 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include "../libft/includes/libft.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include <unistd.h>

static void	send_bit(int server_pid, int bit)
{
	int	signal;

	if (bit == 0)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(server_pid, signal) == -1)
	{
		perror("kill");
		exit(EXIT_FAILURE);
	}
	usleep(5000);
}

static void	send_string(int server_pid, char *str)
{
	int				i;
	int				bit;
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
			i++;
		}
		if (c == '\0')
			break ;
		str++;
	}
}

int	main(int argc, char **argv)
{
	int	server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s <server_pid> <string>\n", argv[0]);
		return (1);
	}
	server_pid = atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_printf("Invalid server PID.\n");
		return (1);
	}
	send_string(server_pid, argv[2]);
	return (0);
}
