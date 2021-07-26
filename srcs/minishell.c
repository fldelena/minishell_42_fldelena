#include "../includes/minishell.h"

void	ft_help_cut(char ***arguments)
{
	int	i;

	i = 0;
	while (arguments[0][i] != NULL)
	{
		arguments[0][i] = cut_quote(arguments[0][i]);
		i++;
	}
}

int	ft_work_with_m_str(t_all *all, char **m_str, char ***arguments)
{
	if (!m_str[0])
		ctrl_d(131);
	if (m_str[0][0] == '\0')
		return (1);
	add_history(m_str[0]);
	if (ft_count_char(m_str[0], ';') > 0)
	{
		print_error(NULL, -2);
		return (1);
	}
	errno = ft_check_command(m_str, all);
	if (errno != 0)
	{
		print_error(m_str[0], -9);
		return (1);
	}
	arguments[0] = ft_split(m_str[0], ';');
	ft_help_cut(arguments);
	return (0);
}

int	ft_check_arg_count(int argc)
{
	if (argc != 1)
	{
		print_error(NULL, -1);
		return (-1);
	}
	return (0);
}

void	ft_signal_main(char **argv, char **m_str, char ***arguments)
{
	(void)argv;
	m_str[0] = 0;
	arguments[0] = NULL;
	signal(SIGINT, &sigint_work);
	signal(SIGQUIT, &sigquit_work);
}

int	main(int argc, char **argv, char **envp)
{
	char	*m_str;
	char	**arguments;
	t_all	*all;

	ft_signal_main(argv, &m_str, &arguments);
	if (ft_check_arg_count(argc) == -1)
		return (-1);
	all = main_struct_malloc(envp);
	make_envp(all, envp);
	while (TRUE)
	{
		init_errno(all);
		unlink("name_tmp");
		free_main(&m_str, arguments, all);
		m_str = readline("minishell: ");
		if (ft_work_with_m_str(all, &m_str, &arguments) == 1)
			continue ;
		ft_launch_arg_n(all, arguments);
		if (ft_open_redirect(all) != 0)
			continue ;
		errno = ft_work_command(arguments, all);
		if (errno != 0)
			print_error(m_str, errno);
	}
	return (errno);
}
