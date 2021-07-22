#include "../includes/minishell.h"

t_env	*env_malloc(char **envp)
{
	t_env	*env;
	int		word_count;

	env = malloc(sizeof(t_env));
	word_count = 0;
	while (*(envp + word_count))
		word_count++;
	env->envp = malloc(sizeof(char *) * (word_count + 1));
	env->var = malloc(sizeof(char *) * (word_count + 1));
	env->val = malloc(sizeof(char *) * (word_count + 1));
	env->f_equal = malloc(sizeof(int) * (word_count + 1));
	return (env);
}

t_lst_pipe	*pipe_lst_malloc(void)
{
	t_lst_pipe	*pipe;

	pipe = malloc(sizeof(t_lst_pipe));
	pipe->count_red_pip = -1;
	pipe->f_red_pip = 0;
	pipe->start_arg = 0;
	pipe->num = -1;
	pipe->command = NULL;
	pipe->next = NULL;
	pipe->prev = NULL;
	return (pipe);
}

// t_parser	*parser_malloc(void)
// {
// 	t_parser	*parser;

// 	parser = malloc(sizeof(t_parser));
// 	parser->count = 0;
// 	parser->o_l_quote = 0;
// 	parser->t_l_quote = 0;
// 	return(parser);
// }

t_all	*main_struct_malloc(char **envp)
{
	t_all	*all;

	all = malloc(sizeof(t_all));
	all->env = env_malloc(envp);
	all->pipe = pipe_lst_malloc();
	// all->parser = parser_malloc();
	return (all);
}
