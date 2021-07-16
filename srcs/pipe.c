#include "../includes/minishell.h"

void	pipe_found(t_pipe *pipe, char *arr)
{
	(void)pipe;
	printf("строка |%s| имеет символов (%zu)\n", arr, ft_strlen(arr));
}


// void	ft_pipe(char **arguments)
// {
// 	int		pipe_fd[2];				//создал массив для пайпа
// 	pid_t	pid;					//создал идентификатор дочернего процесса

// 	pipe(pipe_fd);					//заполнил масив
// 	pid = fork();					// дублируем программку
// 	if (pid == 0)					// если мы в дочернем процессе
// 	{
// 		dup2(fd[1], 1);				// дублируем фдшник в который пишем
// 		close(fd[0]);				// закрываем тот из которого читаем, т.к. нам он тут не нужен
// 		execve("/bin/ls", arguments, 0);
// 		close(fd[1])
// 	}
// 	else
// 	{
// 		dup2(fd[0], 0);				// дублируем fd из которого читаем
// 		close(fd[1]);				// закрывает тот в который пишем, т.к. не нужен
// 		waitpid(pid, 0, 0);
// 		close(fd[0]);
// 	}
// }






// int pipe(int pipefd[2]):
// заполняет масив из двух элементов, переданном в качестве аргумента, файловыми
// дискрипторами. любые данные записанные в [1] могут быть считаны из [0]. Эта
// особеность позволит нам связаться между дочерним и родительским процессом.
// Вернет 0 если работа закончилась корректно, или -1 в противном случае.


// pid_t fork(void):
// Функция порождает дочернюю копию программы (процесс - потомок) возвращает пе-
// ременную типа t_pid. Если значение переменной t_pid == 0 то мы находимся в
// дочернем процессе. Переменную необходимо объявлять собственноручно.


// pid_t waitpid(pid_t pid, int *status, int options):
// Приостанавливает работу текущего процесса до тех пор, пока дочерный процесс
// указаный в параметре pid не завершит выполнение. Возвращает идентификатор до-
// чернего процесса, или нось если доерних процессов нет, или -1 в случае ошибкт.



// int dup2(int oldfd, int newfd):
// создает копию файлового дискриптора. В качестве первого аргумента передается
// дискриптор который будет скопирован, второй аргумент будет являтся дубликатом
// дискриптора. Возвращает в случае ошибки - 1 в случае успешной работы - 0, так
// же в случае ошибки errno устанавливает значение.
// (нам пригодится эта функция в случае использования бинарников, т.к. мы не можем
// менять их файловые дискрипторы, с помощью этой функции мы скопируем fd бинарника
// в fd пайпа. (например ls будет думать что она пишепт в первый fd а она будет пи-
// сать в fd пайпа.))
// всегда менять fd в дочернем процессе



// int execve(const char *filename, char *const argv[], char *const envp[]):
// выполняет программу заданную в первом аргументе, во втором аргументе массив
// строковых параметров, сюда передадим если что наши аргументы, в третьем envp
// При успешном выполнении execve() не возвращает управление. В случае ошибки воз-
// вращается -1, а errno устанавливается в соответствующее значение.



// int close(int fd):
// При вызове функции close() с действительным дескриптором файла, она закрывает
// файл связаный с ним, отчистив при этом буфер. Возвращаяет 0 в случае успеха
// и -1 в случае неуспеха.


//что же надо сделать
// дописать парсинг чтоб он не учитывал пайп (|) как аргумент
// запомнить флаг о том что был замечан пайп, и удалял его из числа аргументов чтоб не мешался
// создать структуру для пайпов в которую я бы заносил аргументы отдельо
// наверное даже придется создать списки
// бинарник ls мы знаем где бинарник cat -e надо отыскать




// почистить место в компе, сдедать все что я написал сверху, поднять парочку контейнеров

// ls | cat -e
// yes | head | wc


// 1:08:30
// 1:25:00
// 45:49
