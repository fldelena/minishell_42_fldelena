#include "../includes/minishell.h"

void free_arr(char **arr)
{
	int i;
	i = -1;

	while (arr[++i])
		free(arr[i]);
	free(arr);
}

void free_main(char **m_str, char **arguments, t_all *all)
{
	int i;
	(void)all;
	t_lst_pipe *tmp;

	while (all->pipe->next)
	{
		tmp = all->pipe;
		all->pipe = all->pipe->next;
		free(tmp);
	}
	free(all->pipe);
	all->pipe = malloc(sizeof(t_lst_pipe));
	all->pipe->next = NULL;
	all->pipe->prev = NULL;
	all->pipe->count_red_pip = -1;
	i = 0;
	if (m_str[0] != NULL)
	{
		free(m_str[0]);
		while (arguments != NULL && arguments[i] != NULL)
		{
			free(arguments[i]);
			i++;
		}
		if (arguments != NULL)
			free(arguments);
	}
}
