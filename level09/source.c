#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_msg {
	char user_str[40];
	char msg_str[140];
	int str_len;
}	t_msg;

void	secret_backdoor()
{
	char	cmd[128];

	fgets(cmd, 128, stdin);
	system(cmd);
}

void	set_msg(t_msg *message)
{
	char	msg_text[1024];

	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(msg_text, 1024, stdin);

	strncpy(message->msg_str, msg_text, message->str_len);
}

void	set_username(t_msg *message)
{
	char	username[140];
	int		i;

	puts(">: Enter your username");
	printf(">>: ");
	fgets(username, 128, stdin);

	i = 0;
	while (i < 40)
	{
		message->user_str[i] = username[i];
		i++;
	}

	printf(">: Welcome, %s", message->user_str);
}

void	handle_msg()
{
	t_msg	message = {0};

	message.str_len = 140;

	set_username(&message);
	set_msg(&message);

	puts(">: Msg sent!");
}

int	main(void)
{
	puts("--------------------------------------------\n"
	"|   ~Welcome to l33t-m$n ~    v1337        |\n"
	"--------------------------------------------");

	handle_msg();

	return (0);
}
