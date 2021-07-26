#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <stdlib.h>

void	rl_replace_line(char *s, int i);

		////////////////////
		// t_lst_pipe *tmp;
		// tmp = all->pipe;
		// while (tmp->next)
		// {
		// 	k = 0;
		// 	printf("num%i : arg = %i, count pipe (редиректов подряд)= %i , тип f_red_pip = %i, fd_redirect = %i\n", tmp->num, tmp->start_arg, tmp->count_red_pip, tmp->f_red_pip, tmp->fd_redirect);
		// 	printf("command : ");
		// 	while (tmp->command[k])
		// 	{
		// 		printf("%s  |  ", tmp->command[k]);
		// 		k++;
		// 	}
		// 	printf("\n");
		// 	tmp = tmp->next;
		// }
		// continue;
		////////////////////
# include <signal.h>
	void	sigint_work(int sig)
{
	(void)sig;
	printf("minishell:   \n");
}

void	ctrl_d(int sig)
{
	printf("minishell: exit\n");
	exit(sig);
}

void	sigquit_work(int sig)
{
	printf("Quit: 3\n");
	(void)sig;
}

int main(int argc, char *argv[], char **env)
{
	// char *yes[2];
	// yes[0] = "/bin/ls";
	// yes[1] = 0;

	// int redirect = open("a", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// int fd1[2];

	// pipe(fd1);
	// close (fd1[1]);
	// fd1[1] = redirect;
	// close(fd1[0]);
	// if (!fork())
	// {
	// 	dup2(fd1[1], 1);
	// 	close(fd1[1]);
	// 	close(fd1[0]);
	// 	execve(yes[0], yes, env);
	// }
	// close(fd1[1]);

	pid_t pid;
	pid = fork();
	pid_t pid2;
	int status;

	if (!pid)
	{
		pid2 = fork();
		if (!pid2)
		{

			exit(43);
		}
		waitpid(pid,&status,0);
		status = WEXITSTATUS(status);
		printf("%d\n",status);
		exit (10);
	}
	waitpid(pid,&status,0);
	status = WEXITSTATUS(status);
	printf("%d\n",status);

}



// #include <sys/types.h>

// int main(int argc, char *argv[], char **env)
// {
// 	// split $PATH для поиска бинарника
// 	//stat()
// 	char *yes[2];
// 	char *head[2];
// 	char *wc[2];
// 	yes[0] = "/usr/bin/yes";
// 	yes[1] = 0;
// 	head[0] = "/usr/bin/head";
// 	head[1] = 0;
// 	wc[0] = "/usr/bin/wc";
// 	wc[1] = 0;
// 	// execve("a", yes, env);
// 	// printf("%s\n", strerror(errno));
// 	int fd1[2];
// 	pipe(fd1);
// 	if (!fork())
// 	{
// 		dup2(fd1[1], 1); // если отдаём
// 		close(fd1[1]);
// 		close(fd1[0]);
// 		execve(yes[0], yes, env);
// 	}
// 	close(fd1[1]);
// 	int fd2[2];
// 	pipe(fd2);
// 	if (!fork())
// 	{
// 		dup2(fd2[1], 1); // если отдаём
// 		close(fd2[1]);
// 		close(fd2[0]);

// 		dup2(fd1[0], 0); //если берем
// 		close(fd1[0]);
// 		close(fd1[1]);
// 		execve(head[0], head, env);
// 	}
// 	close(fd1[0]);
// 	close(fd2[1]);
// 	if (!fork())
// 	{
// 		dup2(fd2[0], 0);
// 		close(fd2[0]);
// 		close(fd2[1]); //если берем
// 		execve(wc[0], wc, env);
// 	}
// 	close(fd2[0]);

// 	wait(0);
// 	wait(0);
// 	wait(0);
// }
