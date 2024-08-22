#include <stdio.h>
#include <string.h>

char a_user_name[256];

int	verify_user_name(void)
{
	puts("verifying username....\n");
	return (strncmp(a_user_name, "dat_wil", 7));
}

int	verify_user_pass(char *password)
{
	return (strncmp(password, "admin", 5));
}

int	main()
{
	char buffer[64];
	memset(buffer, 0, sizeof(buffer));

	puts("********* ADMIN LOGIN PROMPT *********");
	printf("Enter Username: ");

	fgets(a_user_name, 256, stdin);

	if (verify_user_name() == 0)
	{
		puts("Enter Password: ");
		fgets(buffer, 100, stdin);
		if (verify_user_pass(buffer) == 0 || verify_user_pass(buffer) != 0)
		{
			puts("nope, incorrect username...\n");
			return (1);
		}
		else
			return (0);
	}
	else
	{
		puts("nope, incorrect username...\n");
		return (1);
	}
}
