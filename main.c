#include "minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	char	**args;
	t_file	*infile;
	t_file	*outfile;

	while (cmd)
	{
		args = cmd->args;
		infile = cmd->infile;
		outfile = cmd->outfile;
		printf("ARGS :\n");
		while (*args)
		{
			printf("%s\n", *args);
			args++;
		}
		printf("\nINFILES :\n");
		while (infile)
		{
			printf("%s (type = %d)\n", infile->name, infile->type);
			infile = infile->next;
		}
		printf("\nOUTFILES :\n");
		while (outfile)
		{
			printf("%s (type = %d)\n", outfile->name, outfile->type);
			outfile = outfile->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
}

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
