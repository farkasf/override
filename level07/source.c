#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	clear_stdin(void)
{
	int c;

	while (1)
	{
		c = getchar();
		if (c == '\n' || c == EOF)
			return ;
	}
}

unsigned int	get_unum(void)
{
	unsigned int	number;

	fflush(stdout);
	scanf("%u", &number);
	clear_stdin();

	return (number);
}

void	prog_timeout(void)
{
	exit(1);
}

int	store_number(int *num_array)
{
	unsigned int	number;
	int				index;

	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();

	if ((index % 3 == 0) || (index >> 0x18 == 183))
	{
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}

	num_array[index] = number;

	return (0);
}

int	read_number(int *num_array)
{
	int	index;

	printf(" Index: ");
	index = get_unum();

	printf(" Number at data[%u] is %u\n", index, num_array[index]);

	return (0);
}

int	main(int ac, char **av, char **env)
{
	char	input_command[20];
	int		num_array[100];
	int		status;

	while (*av || *env)
	{
		if (*av) 
		{
			memset((void *)*av, 0, strlen(*av));
			++av;
		}
		if (*env)
		{
			memset((void *)*env, 0, strlen(*env));
			++env;
		}
	}

	puts("----------------------------------------------------\n"
		"  Welcome to wil's crappy number storage service!   \n"
		"----------------------------------------------------\n"
		" Commands:                                          \n"
		"    store - store a number into the data storage    \n"
		"    read  - read a number from the data storage     \n"
		"    quit  - exit the program                        \n"
		"----------------------------------------------------\n"
		"   wil has reserved some storage :>                 \n"
		"----------------------------------------------------\n");

	while (1)
	{
		printf("Input command: ");
		fgets(input_command, 20, stdin);
		input_command[strlen(input_command) - 1] = '\0';

		status = 0;

		if (memcmp(input_command, "store", 5) == 0)
			status = store_number(num_array);
		else if (memcmp(input_command, "read", 4) == 0)
			status = read_number(num_array);
		else if ((memcmp(input_command, "quit", 4) == 0))
			return (0);

		if (status == 0)
			printf(" Completed %s command successfully\n", input_command);
		else
			printf(" Failed to do %s command\n", input_command);
		
		memset(input_command, 0, 20);
	}

	return (0);
}
