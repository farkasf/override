#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	int	username[100];
	int	user_pass[42];
	int	sys_pass[100];
	int	read_status;
	FILE	*file;

	file = fopen("/home/users/level03/.pass", "r");
	if (file == (FILE *)0)
	{
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit (1);
	}
	read_status = fread(sys_pass, 1, 41, file);
	sys_pass[strcspn(sys_pass, "\n")] = 0;
	if (read_status != 41)
	{
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit (1);
	}
	fclose(file);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");

	printf("--[ Username: ");
	fgets(username, 100, stdin);
	username[strcspn(username, "\n")] = 0;

	printf("--[ Password: ");
	fgets(user_pass, 100, stdin);
	user_pass[strcspn(user_pass, "\n")] = 0;

	puts("*****************************************");
	if (strncmp(sys_pass, user_pass, 41) == 0)
	{
		printf("Greetings, %s!\n", username);
		system("/bin/sh");
		return (0);
	}
	else
	{
		printf(username);
		puts(" does not have access!");
		exit (1);
	}
}
