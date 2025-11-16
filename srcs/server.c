/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: homura <homura@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:23:52 by homura            #+#    #+#             */
/*   Updated: 2025/11/16 18:29:16 by homura           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <signal.h>
#include "../libft/includes/libft.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include "minitalk.h"
#include <unistd.h>

static void	signal_handler(int signal, siginfo_t *info, void *context)
{
	static int				bit = 0;
	static unsigned char	c = 0;

	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		c |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	act;

	ft_printf("%d\n", getpid());
	act.sa_sigaction = signal_handler;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	sigaddset(&act.sa_mask, SIGUSR2);
	sigaddset(&act.sa_mask, SIGUSR1);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		pause();
}
