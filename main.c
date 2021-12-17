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
	char	*arg1[] = {"echo", "-n", "test de new line", NULL};

	cmd1 = malloc(sizeof(t_cmd));
	cmd1->args = char2_dup(arg1);
	cmd1->input = 0;
	cmd1->output = 1;
	cmd1->input_type = 0;
	cmd1->output_type = PIPE;
	cmd1->infile = NULL;
	cmd1->outfile = NULL;

	t_cmd	*cmd2;
	char	*arg2[] = {"grep", "-o", "avarnier", NULL};

	cmd2 = malloc(sizeof(t_cmd));
	cmd2->args = char2_dup(arg2);
	cmd2->input = 0;
	cmd2->output = 1;
	cmd2->input_type = PIPE;
	cmd2->output_type = 0;
	cmd2->infile = NULL;
	cmd2->outfile = NULL;

	t_cmd	*cmd3;
	char	*arg3[] = {"grep", "-o", "arg2", NULL};

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
	cmd2->next = NULL;
	cmd2->prev = cmd1;
//	cmd3->next = NULL;
//	cmd3->prev = cmd2;

	if (check_file(cmd1) == 0)
	{
		free_shell(env, cmd1);
		return (0);
	}
//	create_pipe(cmd1, env);
//	pid_t pid = fork();
//	if (pid == 0)
		exec_cmd(cmd1, env);
//	pid = fork();
//	if (pid == 0)
//		exec_cmd(cmd2, env);
	
	int	status;
	wait(&status);
//	printf("%i\n", status);
	free_shell(env, cmd1);
	return(0);
}
