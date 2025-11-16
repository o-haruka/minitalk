#include "../libft/includes/libft.h"
#include "../libft/stdio/ft_printf/ft_printf.h"
#include "../include/minitalk.h"

// static void	signal_handler(int signal, siginfo_t *info, void *context)
// {
// 	static int	bit = 0;
// 	static unsigned char	c = 0;

// 	(void)context;
// 	(void)info;
// 	if (signal == SIGUSR1)
// 		c |= (1 << bit);
// 	bit++;
// 	if (bit == 8)
// 	{
// 		ft_printf("%c", c);
// 		bit = 0;
// 		c = 0;
// 	}
// }
static void	signal_handler(int signal, siginfo_t *info, void *context)
{
    static int bit = 0;
    static unsigned char c = 0;

    (void)context;
    (void)info;

    if (signal == SIGUSR1)
        c |= (1 << bit);         // 1ビット
    else if (signal == SIGUSR2)
        c &= ~(1 << bit);        // 0ビット ←これが抜けていた!!

    bit++;
    if (bit == 8)
    {
        ft_printf("%c", c);
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