#include "minishell.h"
#include <stdio.h>

int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	cmd->name = ft_strdup("echo");
	cmd->option = NULL;
	cmd->arg = ft_strdup("avarnier login 42 test");
	cmd->input = 0;
	cmd->output = 1;
	cmd->next = NULL;
	cmd->prev = NULL;

	t_cmd	*cmd2;

	cmd2 = malloc(sizeof(t_cmd));
	cmd2->name = ft_strdup("grep");
	cmd2->option = NULL;
	cmd2->arg = ft_strdup("login");
	cmd2->input = 0;
	cmd2->output = 1;
	cmd2->next = NULL;
	cmd2->prev = cmd;
	cmd->next = cmd2;

	t_cmd *cmd3;

	cmd3 = malloc(sizeof(t_cmd));
	cmd3->name = ft_strdup("grep");
	cmd3->option = ft_strdup("-o");
	cmd3->option = ft_strdup("avarnier");
	cmd3->input = 0;
	cmd3->output = 1;
	cmd3->next = NULL;
	cmd3->prev = cmd2;
	cmd2->next = cmd3;

	t_env	*env;

	env = NULL;
	add_to_env("PATH", getenv("PATH"), &env);

	t_shell *shell;

	shell = malloc(sizeof(t_shell));
	shell->cmd  = cmd;
	shell->env = env;

	create_pipe(cmd, env, shell);
	create_pipe(cmd2, env, shell);
	pid_t pid = fork();

	if (pid == 0)
		exec_cmd(cmd, env, shell);
	pid = fork();
	if (pid == 0)
		exec_cmd(cmd2, env, shell);
//	pid = fork();
//	if (pid == 0)
//		exec_cmd(cmd3, env, shell);
	int i = 0;
	wait(&i);
	free_shell(shell);
//	pid_t pid = fork();
//	if (pid == 0)
//		exec_cmd(cmd, env, shell);
//	if (pid > 0)
//		free_shell(shell);
	return(0);
}
