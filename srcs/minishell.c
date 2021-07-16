#include "../includes/minishell.h"

void print_error(char *command, int my_error)
{
	if (my_error > 0)
		errno = my_error;
	else
		errno = -1;
	if (my_error == -1)
		printf("minishell: too much arguments\n");
	else if (my_error == -2)
		printf("minishell: Too much command in one string\n");
	else if (my_error == 127)
		printf("minishell: %s: command not found\n", command);
	else if (my_error == 1)
		printf("minishell: Not valid\n");
	else
		return ;
}

void free_main(char **m_str,char **arguments)
{
	int i;

	i = 0;
	if (m_str[0] != NULL)
	{
		free(m_str[0]);
		while(arguments != NULL && arguments[i] != NULL)
		{
			free(arguments[i]);
			i++;
		}
		if (arguments != NULL)
			free(arguments);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void) argv;
	char	*m_str;
	int		i;
	char	**arguments;
	t_all	*all;

	m_str = 0;
	arguments = NULL;
	if (argc != 1)					// не должен принимать никаких аргументов
	{
		print_error(NULL, -1);
		return (-1);
	}
	all = main_struct_malloc(envp);
	make_envp(all, envp);
	while (TRUE)
	{
		errno = 0;		// ИСПРАВИТЬ так как при вызове команды $? предыдущее значение обнулится
		free_main(&m_str, arguments);
		m_str = readline("minishell: ");
		if (m_str[0] == '\0')						// вывод ошибки чтения строки
			continue ;
		add_history(m_str);
		if(ft_count_char(m_str, ';') > 0)			// вывод ошибки количества команд
		{
			print_error(NULL, -2);
			continue ;
		}
		errno = ft_check_command(&m_str, all);		// проверка валидности введенной команды
		if (errno != 0)
		{
			print_error(m_str, errno);
			continue ;
		}
		arguments = ft_split(m_str, ';');			// разделим команду на аргументы
		i = 0;
		while(arguments[i] != NULL)
		{
			// printf("до |%s|\n", arguments[i]);
			arguments[i] = cut_quote(arguments[i]);
			// printf("после |%s|\n", arguments[i]);
			i++;
		}

//		ВНИМАНИЕ! тестовый участок! экспериментирую с пайпами!

		// if (0)						// проверка флага или чего-то там еще на наличие пайпа
		// 	ft_pipe(arguments);


		// i = 0;
		// while (*(arguments + i) != NULL)
		// {
		// 	printf("аргументы![%d] %s\n", i, arguments[i]);
		// 	i++;
		// }
//		ВНИМАНИЕ! конец тестового участка!

		ft_work_command(arguments, all);
		if (errno != 0)						// вывод ошибки cd реализовал внутри
		{
			print_error(m_str, errno);
			continue ;
		}
	}
}
