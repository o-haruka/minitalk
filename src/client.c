#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/minitalk.h"

void send_bit(int server_pid, int bit)
{
	int signal = (bit == 0) ? SIGUSR1 : SIGUSR2;
	if (kill(server_pid, signal) == -1)
	{
		perror("kill");
		exit(EXIT_FAILURE);
	}
	usleep(100);
}

void send_string(int server_pid, char *str)
{
	int i, bit;
	while (1)
	{
		unsigned char c = *str;
		for (i = 0; i < 8; i++)
		{
			bit = (c >> i) & 1;
			send_bit(server_pid, bit);
		}
		if (c == '\0')
			break;
		str++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s <server_pid> <string>\n", argv[0]);
		return (1);
	}
	int server_pid = atoi(argv[1]);
	if (server_pid <= 0)
	{
		printf("Invalid server PID.\n");
		return (1);
	}
	send_string(server_pid, argv[2]);
	return (0);
}