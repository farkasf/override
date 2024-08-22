#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>

int	auth(char *username, int serial)
{
	int	hash;
	int	username_len;
	int	i;

	i = 0;
	username[strcspn(username, "\n")] = 0;

	username_len = strnlen(username, 32);
	if (username_len <= 5)
		return (1);
	
	if (ptrace(0, 0, 1, 0) == -1)
	{
		puts("\x1B[32m.---------------------------.");
		puts("\x1B[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1B[32m'---------------------------'");
		return (1);
	}

	hash = ((int)username[3] ^ 4919) + 6221293;
	while (i < username_len)
	{
		if (username[i] < ' ')
			return (1);
		hash += ((int)username[i] ^ hash) % 1337;
		i++;
	}

	if (serial == hash)
		return (0);
	else
		return (1);
}

int	main(void)
{
	char	username[32];
	int		serial;

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");

	printf("-> Enter Login: ");
	fgets(username, 32, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");

	printf("-> Enter Serial: ");
	scanf("%d", &serial);

	if (auth(username, serial) == 0)
	{
		puts("Authenticated!");
		system("/bin/sh");
		return (0);
	}
	else
		return (1);
}
