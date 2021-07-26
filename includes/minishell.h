#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

# define TRUE 1


pid_t	g_pid;
int		g_sig;
// структура для окружения

typedef struct s_env
{
	char	**envp;
	char	**var;
	char	**val;
	int		*f_equal;
}				t_env;

//структура для списка пайпов

typedef struct s_lst_pipe
{
	pid_t				pid;
	char				**command;
	int					fd_redirect;
	int					fd_pid[2];
	int					count_red_pip;		// сколько подряд пайпов или редиректов
	int					f_red_pip;			// если пайп то 1 , если > или >> то = 2 | если < или << то 3
	int					start_arg;			// на каком аргументе начинается пайп
	int					num;				// положение листа в списке // delete me
	struct s_lst_pipe	*next;				// следующий элемент списка
	struct s_lst_pipe	*prev;				// предыдущий
}				t_lst_pipe;

typedef struct s_parser
{
	int	o_l_quote;
	int	t_l_quote;
	int	count;
}				t_parser;

// главная структура

typedef struct s_all
{
	t_env		*env;
	t_lst_pipe	*pipe;
	t_parser	parser;
}				t_all;

int		ft_check_command(char **m_str, t_all *all);
int		ft_work_command(char **arguments, t_all *all);
int		ft_echo(t_all *all, int fd, char **arguments);
int		ft_cd(char **arguments, t_all *all);
int		ft_env(t_all *all);
int		ft_export(t_all *all, char **arguments);
int		ft_unset(t_all *all, char **arguments);
int		binary_work(t_all *all, char **arguments);
int		*add_f_equal(char **envp, int words);
int		ft_count_env(char *m_str, int *i, int l_dollar);
int		ft_count_befor(int count, char *m_str, char *now_env, int i);
int		ft_before_env(char *m_str, char *now_env, int count, char *m2);
int		find_env_in_all(t_all *all, char *now_env);
int		ft_rewrite(char **m_str, char *now_env, t_all *all, int count);
int		ft_dollar(char **m_str, int *i, t_all *all);
int		ft_check_pip_red_help2(char **m_str, t_all *all, int *i, int *c_pip);
int		ft_check_pip_red_help1(char **m_str, t_all *all, int *i, int *c_pip);
int		ft_add_lst(t_all *all, int c_pip, int count, int f_dir);
int		ft_check_error(int c_pip, int f_dir);
int		ft_check_pip_red(char **m_str, t_all *all, int *i);
int		ft_open_redirect(t_all *all);
int		exception(char **arguments);
int		ft_exit(char **arguments);
char	*cut_quote(char *arg);
char	*ft_help1(char *m_str, int *i, int count);
char	*ft_help2(char *m_str, int *i, int count);
char	**arr_copy(char **envp);
char	**add_envp(char **envp, char **arguments, int words);
char	**add_var_val(char **arr, char **arguments, int words, int index);
char	**ft_make_arg_n(char **arguments, t_all *all, int num);
t_all	*main_struct_malloc(char **envp);
void	free_main(char **m_str, char **arguments, t_all *all);
void	add_variable(t_env *env, char **arguments);
void	similar_var(t_env *env, char **arguments);
void	del_similar_var(t_env *env, int index);
void	free_arr(char **arr);
void	make_envp(t_all *all, char **envp);
void	pipe_found(t_lst_pipe *pipe, char *arr);
void	ft_write_env(int i, char *m2, t_all *all, int *j_m);
void	ft_end_rewrite(char *m2, char *m_str, int j_m, int j_str);
void	ft_add_lst_2(t_lst_pipe *tmp, int c_pip, int count, int f_dir);
void	ft_lst_null(t_lst_pipe **tmp, int *num2);
void	ft_first(char *m_str, int *t_l_quote, int *o_l_quote, int *i);
void	rl_replace_line();
void	sigint_work(int sig);
void	ctrl_d(int sig);
void	sigquit_work(int sig);
void	ft_correct_rir(t_all *all);
void	ft_rewrite_arg_cat(t_lst_pipe *tmp);
void	ft_two_red_arg_cat(t_lst_pipe *tmp);
void	ft_reddir_right(t_lst_pipe *tmp);
void	ft_red_left_one(t_lst_pipe *tmp);
void	ft_red_left_double(t_lst_pipe *tmp);
void	ft_for_norm(t_lst_pipe *tmp);

#endif
