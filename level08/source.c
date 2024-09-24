#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

void	log_wrapper(FILE *file, char *log, char *filename)
{
	char	buffer[264];

	strcpy(buffer, log);
	snprintf(buffer + strlen(buffer), 254 - strlen(buffer), filename);
	buffer[strcspn(buffer, "\n")] = 0;

	fprintf(file, "LOG: %s\n", buffer);

	return ;
}

int	main(int ac, char **av)
{
	char	buffer[104];
	int		fd;
	int		c;
	FILE	*log_f;
	FILE	*backup_f;

	if (ac != 2)
		printf("Usage: %s filename\n", av[0]);

	backup_f = fopen(av[1], "r");
	if (backup_f == 0)
	{
		printf("ERROR: Failed to open %s\n", av[1]);
		exit(1);
	}
	
	log_f = fopen("./backups/.log", "w");
	if (log_f == 0)
	{
		printf("ERROR: Failed to open ./backups/.log\n");
		exit(1);
	}

	log_wrapper(log_f, "Starting back up: ", av[1]);

	strcpy(buffer, "./backups/");
	strncat(buffer, av[1], 99 - strlen(buffer));

	fd = open(buffer, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd < 0)
	{
		printf("ERROR: Failed to open ./backups/%s\n", av[1]);
		exit(1);
	}

	c = fgetc(backup_f);
	while (c != EOF)
	{
		write(fd, &c, 1);
		c = fgetc(backup_f);
	}

	log_wrapper(log_f, "Finished back up: ", av[1]);

	fclose(backup_f);
	close(fd);
	return (0);
}
