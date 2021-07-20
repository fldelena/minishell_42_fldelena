#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TRUE 1

// структура для окружения

typedef struct s_env
{

	char **envp;
	char **var;
	char **val;
	int *f_equal; // f - значит флаг. этот значит флаг знака '='

} t_env;

//структура для списка пайпов
typedef struct s_lst_pipe
{
	pid_t pid;
	int fd_pid[2];
	int count_red_pip;				 // сколько подряд пайпов или редиректов
	int f_red_pip;			 // если пайп то 1 , если > или >> то = 2 | если < или << то 3
	int start_arg;				 // на каком аргументе начинается пайп
	int num;				 // положение листа в списке // delete me
	struct s_lst_pipe *next; // следующий элемент списка
	struct s_lst_pipe *prev;
} t_lst_pipe;

// структура для списка редиректов

typedef struct s_lst_red
{
	struct s_lst_red *next; // следующий элемент списка
} t_lst_red;

// главная структура

typedef struct s_all
{
	t_env *env;
	t_lst_pipe *pipe;
} t_all;

int ft_check_command(char **m_str, t_all *all);
char *cut_quote(char *arg);
int is_n_flag(char *s);
void add_variable(t_env *env, char **arguments);
int ft_work_command(char **arguments, t_all *all);
void free_main(char **m_str, char **arguments, t_all *all);
void line_sort(char **envp);
void add_variable(t_env *env, char **arguments);
void del_variable(t_env *env, char **arguments);
char **arr_copy(char **envp);
void free_arr(char **arr);
void make_envp(t_all *all, char **envp);
t_all *main_struct_malloc(char **envp);

void pipe_found(t_lst_pipe *pipe, char *arr);
int binary_work(t_all *all, char **arguments);
// void			ft_pipe(char **arguments);

#endif
