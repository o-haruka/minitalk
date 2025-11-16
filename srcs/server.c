/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 19:20:46 by homura            #+#    #+#             */
/*   Updated: 2025/11/16 19:50:18 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include "../libft/includes/libft.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;

	(void)info;
	(void)context;
	if (signum == SIGUSR2)
		c |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (c == '\0')
			write(1, "\n", 1);
		else
			write(1, &c, 1);
		c = 0;
		bit_count = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
