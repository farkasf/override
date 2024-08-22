#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/prctl.h>
#include <sys/wait.h>

int	main(void)
{
	char	buffer[32];
	int		check;

	pid_t	fork_pid;
	pid_t	wait_pid;
	pid_t	next_pid;
	
	fork_pid = fork();

	if (fork_pid == 0)
	{
		prctl(1, 1);
		ptrace(0, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(buffer);
	}
	else
	{
		while (check != 11)
		{
			wait(&wait_pid);
			next_pid = wait_pid;
			if (WIFEXITED(next_pid))
			{
				puts("child is exiting...");
				return (0);
			}
			check = ptrace(3, fork_pid, 44, 0);
		}
		puts("no exec() for you");
		kill(fork_pid, 9);
	}

	return (0);
}
