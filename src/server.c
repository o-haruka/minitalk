#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/minitalk.h"

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static unsigned char c = 0;
	static int bit_count = 0;
	(void)info;
	(void)context;

	if (signum == SIGUSR2)
		c |= (1 << bit_count); // SIGUSR2=1
	// SIGUSR1=0は何もしない
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &c, 1);
		if (c == '\0') {
			// 文字列終端時の処理（必要ならカウンタリセット等）
		}
		c = 0;
		bit_count = 0;
	}
}

int main(void)
{
	struct sigaction sa;
	pid_t pid = getpid();
	printf("Server PID: %d\n", pid);

	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);

	while (1)
		pause();
	return (0);
}