#include "../includes/minishell.h"

void	sigint_work(int sig)
{
	(void)sig;
	if (g_pid == 0)
		printf("minishell:   \n");
    else
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void	ctrl_d(int sig)
{
	printf("minishell: exit\n");
	exit(sig);
}

void	sigquit_work(int sig)
{
	printf("^\\Quit: 3\n");
	exit(sig);
}
