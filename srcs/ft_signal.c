#include "../includes/minishell.h"

void	sigint_work(int sig)
{
	(void)sig;
	printf("minishell:   \n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


void	ctrl_d(int sig)
{
	printf("minishell: exit\n");
	exit(sig);
}

// void	sigquit_work(int sig)
// {
// 	(void) sig;
// }
