#include "../includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	*m_str = 0;
	int		res_work;
	int		i;
	(void) argv;

	if (argc != 1)
        return (-1);								// не должен принимать никаких аргументов
	while (TRUE)
	{
		i = 0;
		m_str = readline("minishell: ");
		if (m_str == NULL)							// вывод ошибки чтения строки
			return (-1);
		add_history(m_str);

		// if(ft_count_char(m_str, ';') > 1)		// вывод ошибки количества команд // (закоментил на время), т,к, мешало работе проекта
		// 	return (-1);

		res_work = ft_check_command(m_str);			// проверка валидности введенной команды

		char **arguments;
		// if (m_str != NULL)						// arguments не инициализированна, всвязи с чем не компилится (закоментил на время)
		// {
		// 	free(m_str);
		// 	while(arguments != NULL && arguments[i] != NULL)
		// 	{
		// 		free(arguments[i]);
		// 		i++;
		// 	}
		// 	if (arguments != NULL)
		// 		free(arguments);
		// }
		arguments = ft_split(m_str, ';');			// разделим команду на аргументы

		i = 1;
		while(arguments[i] != NULL)
		{
			printf("%s\n", arguments[i]);
			arguments[i] = cut_quote(arguments[i]);	// проблема с кейсом  cd adsdf "dsfds" """sdh  sjd""" и с экранированием  + "asdsa""asdasd"
			printf("%s\n", arguments[i]);
			i++;
		}

		if (res_work == 0)
			res_work += ft_work_command(arguments, envp);	// не проверяем аргументы и даже правильность команды,
															// Тут просто пихаем в нужную команду его аргументы или если команды нет выдаём ошибку!
		if (res_work != 0)
			return (-1);									// выход из бесконечного цыкла - ok? (поставил -1 вместо erno)


		// int i = -1;
		// while (arguments[++i])
		// 	free(arguments[i]);
		// free(arguments);
	}
}

// тест cd "qwewqe""  qwe  "qwe            "123"
