#include "minishell.h"

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
	while (ret)
	{
		add_history(ret);
		cmd = ft_parse_line(ret, &env);
		to_free = cmd;
		exec_all_cmd(cmd, env);
		free(ret);
		free_cmd(to_free);
		ret = readline("minishell>$");
	}
	free_env(env);
}
