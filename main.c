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

/*void	ft_print_cmd(t_cmd *cmd)
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
	while (ret)
	{
		add_history(ret);
		cmd = ft_parse_line(ret, &env);
		to_free = cmd;
		ft_print_cmd(cmd);
		free(ret);
		free_cmd(to_free);
		ret = readline("minishell>$");
	}
	free_env(env);
}*/

/*int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
 	add_to_env("PWD", getenv("PWD"), &env);
 	add_to_env("OLDPWD", getenv("OLDPWD"), &env);
 	add_to_env("HOME", getenv("HOME"), &env);
 	add_to_env("PATH", getenv("PATH"), &env);
	add_to_env("?", "1", &env);

 	t_cmd	*cmd1;
 	char	*arg1[] = {"grep", "robot", NULL};

 	cmd1 = malloc(sizeof(t_cmd));
 	cmd1->args = char2_dup(arg1);
 	cmd1->input = 0;
 	cmd1->output = 1;
	cmd1->infile = malloc(sizeof(t_file));
	cmd1->infile->type = HEREDOC;
	cmd1->infile->name = ft_strdup("eof");
	cmd1->infile->next = malloc(sizeof(t_file));
	cmd1->infile->prev = NULL;
	cmd1->infile->next->prev = cmd1->infile;
	cmd1->infile->next->next = NULL;
	cmd1->infile->next->type = HEREDOC;
	cmd1->infile->next->name = ft_strdup("eof");
	cmd1->outfile = malloc(sizeof(t_file));
	cmd1->outfile->type = PIPE;
	cmd1->outfile->name = NULL;
	cmd1->outfile->next = NULL;
	cmd1->outfile->prev = NULL;

 	t_cmd	*cmd2;
 	char	*arg2[] = {"grep", "-o", "robot", NULL};

 	cmd2 = malloc(sizeof(t_cmd));
 	cmd2->args = char2_dup(arg2);
 	cmd2->input = 0;
 	cmd2->output = 1;
	cmd2->infile = malloc(sizeof(t_file));
	cmd2->infile->type = PIPE;
	cmd2->infile->name = NULL;
	cmd2->infile->next = NULL;
	cmd2->infile->prev = NULL;
	cmd2->outfile = malloc(sizeof(t_file));
	cmd2->outfile->type = REPLACE;
	cmd2->outfile->name = ft_strdup("res1");
	cmd2->outfile->next = NULL;
	cmd2->outfile->prev = NULL;

 	cmd1->next = cmd2;
 	cmd1->prev = NULL;
 	cmd2->next = NULL;
 	cmd2->prev = cmd1;

	ft_env(env);
	exec_all_cmd(cmd1, env);

 	free_shell(env, cmd1);
 	return(0);
}*/
