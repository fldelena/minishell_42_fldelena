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
	char **command;
	int	fd_redirect;
	int fd_pid[2];
	int count_red_pip;				// сколько подряд пайпов или редиректов
	int f_red_pip;					// если пайп то 1 , если > или >> то = 2 | если < или << то 3
	int start_arg;					// на каком аргументе начинается пайп
	int num;						// положение листа в списке // delete me
	struct s_lst_pipe *next;		// следующий элемент списка
	struct s_lst_pipe *prev;		// предыдущий
} t_lst_pipe;

typedef struct s_parser
{
	int	o_l_quote;
	int	t_l_quote;
	int count;
} t_parser;

// главная структура

typedef struct s_all
{
	t_env *env;
	t_lst_pipe *pipe;
	// t_parser *parser;
	t_parser parser;
} t_all;

int		ft_echo(int fd, char **arguments);
int		ft_check_command(char **m_str, t_all *all);
char	*cut_quote(char *arg);
int		is_n_flag(char *s);
void	add_variable(t_env *env, char **arguments);
int		ft_work_command(char **arguments, t_all *all);
void	free_main(char **m_str, char **arguments, t_all *all);
int		ft_cd(char **arguments, t_env *env);
int		ft_env(t_env *env);
int 	ft_export(t_env *env, char **arguments);
void	line_sort(char **envp);
void	add_variable(t_env *env, char **arguments);
void	del_variable(t_env *env, char **arguments);
char	**arr_copy(char **envp);
void	free_arr(char **arr);
void	make_envp(t_all *all, char **envp);
t_all	*main_struct_malloc(char **envp);
void	pipe_found(t_lst_pipe *pipe, char *arr);
int		binary_work(t_all *all, char **arguments);
char 	**ft_make_arg_n(char **arguments, t_all *all, int num);
// void			ft_pipe(char **arguments);

char	*ft_help1(char *m_str, int *i, int count);
char	*ft_help2(char *m_str, int *i, int count);
int	ft_count_env(char *m_str, int *i, int l_dollar);
int	ft_count_befor(int count, char *m_str, char *now_env, int i);
int	ft_before_env(char *m_str, char *now_env, int count, char *m2);
void	ft_write_env(int i, char *m2, t_all *all, int *j_m);
void	ft_end_rewrite(char *m2, char *m_str, int j_m, int j_str);
int	find_env_in_all(t_all *all, char *now_env);
int	ft_rewrite(char **m_str, char *now_env, t_all *all, int count);
int	ft_dollar(char **m_str, int *i, t_all *all);
int	ft_check_pip_red_help2(char **m_str, t_all *all, int *i, int *c_pip);
int	ft_check_pip_red_help1(char **m_str, t_all *all, int *i, int *c_pip);
int	ft_add_lst(t_all *all, int c_pip, int count, int f_dir);
void	ft_add_lst_2(t_lst_pipe *tmp, int c_pip, int count, int f_dir);
void	ft_lst_null(t_lst_pipe **tmp, int *num2);
int	ft_check_error(int c_pip, int f_dir);
void	ft_first(char *m_str, int *t_l_quote, int *o_l_quote, int *i);
int	ft_check_pip_red(char **m_str, t_all *all, int *i);
int ft_open_redirect(t_all *all);
int exception(char **arguments);

#endif
