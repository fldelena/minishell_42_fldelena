#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TRUE 1

// структура для окружения

typedef struct s_env {

	char	**envp;
	char	**var;
	char	**val;
	int		*f_equal;			// f - значит флаг. этот значит флаг знака '='

} t_env;

//структура для списка пайпов

typedef struct s_lst_pipe {

	char **argument;				// сам аргумент
	int f_pipe;					// количество пайпов подряд
	int arg_p;					// на каком аргументе начинается пайп
	int num;					// положение листа в списке
	struct s_lst_pipe *next;	// следующий элемент списка
} t_lst_pipe;

// структура для списка редиректов

typedef struct s_lst_red {
	struct s_lst_red *next;	// следующий элемент списка
} t_lst_red;

// главная структура

typedef struct s_all {

	t_env		*env;
	t_lst_pipe	*pipe;
	t_lst_red	*redir;

} t_all;

int				ft_check_command(char **m_str, t_all *all);
char			*cut_quote(char *arg);
int				is_n_flag(char *s);
void			add_variable(t_env *env, char **arguments);
int				ft_work_command(char **arguments, t_all *all);
void 			free_main(char **m_str,char **arguments, t_all *all);
void			line_sort(char **envp);
void			add_variable(t_env *env, char **arguments);
void			del_variable(t_env *env, char **arguments);
char			**arr_copy(char **envp);
void			free_arr(char **arr);
void			make_envp(t_all *all, char **envp);
t_all			*main_struct_malloc(char **envp);

void			pipe_found(t_lst_pipe *pipe, char *arr);
// void			ft_pipe(char **arguments);

#endif
