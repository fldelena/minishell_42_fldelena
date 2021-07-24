#include "../includes/minishell.h"


// void signal_h(int sig)
// {
// 	(void)sig;
// 	if (g_pid )
// 		return ;
// }

void print_error(char *command, int my_error)
{
	if (my_error > 0)
		errno = my_error;
	else
		errno = -1;
	if (my_error == -1)
		write(2, "minishell: too much arguments\n", 61);
	else if (my_error == -2)
		write(2, "minishell: Too much command in one string\n", 42);
	else if (my_error == -3)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	else if (my_error == -4)
		write(2, "minishell: syntax error near unexpected token `||'\n", 51);
	else if (my_error == -5)
		write(2, "minishell: syntax error near unexpected token `>'\n", 51);
	else if (my_error == -6)
		write(2, "minishell: syntax error near unexpected token `>>'\n", 51);
	else if (my_error == -7)
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
	else if (my_error == -8)
		write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
	else if (my_error == 127)
		printf("minishell: %s: command not found\n", command); // тут исправить вывод ошибки
	else if (my_error == 1)
		write(2, "minishell: Not valid\n", 21);
	else
		printf("%s\n", strerror(errno));
}

void init_errno(t_all *all)
{
	char **arguments;
	char *error_my;
	char *dollar;

	dollar = malloc(3);
	dollar[0] = '?';
	dollar[1] = '=';
	dollar[2] = '\0';
	error_my = ft_itoa(errno);
	dollar = ft_strjoin(dollar, error_my);
	arguments = malloc(sizeof(char *) * 3);
	arguments[0] = "hi\0";
	arguments[1] = dollar;
	arguments[2] = NULL;
	add_variable(all->env, arguments);

	all->parser.count = 0;
	all->parser.o_l_quote = 0;
	all->parser.t_l_quote = 0;
	errno = 0;
}

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	char *m_str;
	int i;
	char **arguments;
	t_all *all;

	m_str = 0;
	arguments = NULL;
	signal(SIGINT, &signal_work);
	signal(SIGQUIT, &signal_work);
	if (argc != 1) // не должен принимать никаких аргументов
	{
		print_error(NULL, -1);
		return (-1);
	}
	all = main_struct_malloc(envp);
	make_envp(all, envp);
	while (TRUE)
	{
		init_errno(all);
		free_main(&m_str, arguments, all);
		m_str = readline("minishell: ");
		if (m_str[0] == '\0') // вывод ошибки чтения строки
			continue;
		add_history(m_str);
		if (ft_count_char(m_str, ';') > 0) // вывод ошибки количества команд
		{
			print_error(NULL, -2);
			continue;
		}
		////////////////// ТУТ УМИРАЕТ errno ИЗ МИНИШЕЛЛА В ПАЙПЕ
		errno = ft_check_command(&m_str, all); // проверка валидности введенной команды
		if (errno != 0)
		{
			print_error(m_str, errno);
			continue;
		}

		arguments = ft_split(m_str, ';'); // разделим команду на аргументы
		i = 0;
		while (arguments[i] != NULL)
		{
			arguments[i] = cut_quote(arguments[i]);
			i++;
		}

		t_lst_pipe *tmp_123; // заполняю в структуру
		int k;
		k = 0;
		tmp_123 = all->pipe;
		while (tmp_123->next)
		{
			tmp_123->command = ft_make_arg_n(arguments, all, k);
			tmp_123 = tmp_123->next;
			k++;
		}
		ft_open_redirect(all);
		if (errno != 0)
		{
			printf("minishell: %s\n", strerror(errno));
			continue ;
		}
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
		errno = ft_work_command(arguments, all);
		if (errno != 0) // вывод ошибки cd реализовал внутри
			print_error(m_str, errno);
	}
	return (errno);
}
