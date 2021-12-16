#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
	
	add_to_env(NULL, NULL, &env);
	add_to_env("PWD", getenv("PWD"), &env);
	add_to_env("OLDPWD", getenv("OLDPWD"), &env);
	add_to_env("HOME", getenv("HOME"), &env);
	add_to_env("PATH", getenv("PATH"), &env);

	t_cmd	*cmd1;
	char	*arg1[] = {"cat", "main.c", NULL};

	cmd1 = malloc(sizeof(t_cmd));
	cmd1->args = char2_dup(arg1);
	cmd1->input = 0;
	cmd1->output = 1;
	cmd1->input_type = 0;
	cmd1->output_type = PIPE;
	cmd1->infile = NULL;
	cmd1->outfile = NULL;

	t_cmd	*cmd2;
	char	*arg2[] = {"grep", "PWD", NULL};

	cmd2 = malloc(sizeof(t_cmd));
	cmd2->args = char2_dup(arg2);
	cmd2->input = 0;
	cmd2->output = 1;
	cmd2->input_type = PIPE;
	cmd2->output_type = PIPE;
	cmd2->infile = NULL;
	cmd2->outfile = NULL;

	t_cmd	*cmd3;
	char	*arg3[] = {"grep", "-o", "&env", NULL};

	cmd3 = malloc(sizeof(t_cmd));
	cmd3->args = char2_dup(arg3);
	cmd3->input = 0;
	cmd3->output = 1;
	cmd3->input_type = PIPE;
	cmd3->output_type = 0;
	cmd3->infile = NULL;
	cmd3->outfile = NULL;

	cmd1->next = cmd2;
	cmd1->prev = NULL;
	cmd2->next = cmd3;
	cmd2->prev = cmd1;
	cmd3->next = NULL;
	cmd3->prev = cmd2;

	t_shell	*shell;
	shell = malloc(sizeof(t_shell));
	shell->env = env;
	shell->cmd = cmd1;

	pid_t	pid;
	create_pipe(cmd1, env, shell);
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd1, env, shell);
	create_pipe(cmd2, env, shell);
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd2, env, shell);
	close(cmd1->output);
	close(cmd2->input);
	cmd1->output = 1;
	cmd2->input = 0;
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd3, env, shell);
	wait(NULL);
	free_shell(shell);
	return(0);
}
