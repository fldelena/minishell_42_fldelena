#include "../includes/minishell.h"

void		free_arr(char **arr)
{
	int i;
	i = -1;

	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void free_main(char **m_str,char **arguments, t_all *all)
{
	int i;
	(void)all;
	t_lst_pipe *tmp;

	while (all->pipe)
	{
		tmp = all->pipe;
		all->pipe = all->pipe->next;
		free(tmp);
	}
	all->pipe = malloc(sizeof(t_lst_pipe));
	all->pipe->next = NULL;
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