#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void	decrypt(unsigned int key)
{
	char	array[] = "Q}|u`sfg~sf{}|a3";
	int		i;

	i = 0;
	while (array[i])
	{
		array[i] = array[i] ^ key;
		i++;
	}

	if (strcmp(array, "Congratulations!") == 0)
		system("/bin/sh");
	else
		puts("\nInvalid Password");
}

void	test(unsigned int input, int number)
{
	int	key;

	key = number - input;

	if (key > 21)
		decrypt(rand());
	else
		decrypt(key);
}

int	main(void)
{
	unsigned int	input;

	srand(time(0));

	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");

	scanf("%u", &input);
	test(input, 322424845);

	return (0);
}
