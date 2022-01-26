#include "minishell.h"

int	g_exit;

int	main(int ac, char **av, char **envp)
{
	t_env	*env;
	t_cmd	*cmd;
	t_cmd	*to_free;
	char	*ret;

	(void) ac;
	(void) av;
	env = NULL;
	env = ft_parse_env(envp);
	ret = readline("minishell>$");
//	signal(SIGINT, ft_handler);
	while (ret)
	{
		add_history(ret);
		cmd = ft_parse_line(ret, &env);
		to_free = cmd;
		exec_all_cmd(cmd, env);
//		ft_print_cmd(cmd);
		free(ret);
		if (to_free != NULL)
			free_cmd(to_free);
		ret = readline("minishell>$");
	}
	free_env(env);
}
