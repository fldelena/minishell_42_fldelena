#include "../includes/minishell.h"

void	signal_work(int sig)
{
	if (g_pid)
	{
		if (sig == SIGQUIT)
			printf("quit\n");
		kill(g_pid,sig);
		g_pid = 0;
	} else if ( sig == SIGINT)
		write(1,"\nminishell:",11);

}
