#include "minishell.h"

/*int main(int argc, char **argv, char **envp)
{
	t_cmd	*cmd;
	t_env	*env;
	char	*line;

	env = NULL;
	env = ft_parse_env(envp);
	
	line = readline("minishell: ");
	while (line)
	{
		add_history(line);
		cmd = ft_parse_line(line, &env);
		exec_all_cmd(cmd, env);
		free_cmd(cmd);
		free(line);
		line = readline("minishell: ");
	}
	
	return(0);
}*/

int main()
{
	t_env	*env;

	env = NULL;
	add_to_env(NULL, NULL, &env);
 	add_to_env("PWD", getenv("PWD"), &env);
 	add_to_env("OLDPWD", getenv("OLDPWD"), &env);
 	add_to_env("HOME", getenv("HOME"), &env);
 	add_to_env("PATH", getenv("PATH"), &env);

 	t_cmd	*cmd1;
 	char	*arg1[] = {"grep", "robot",NULL};

 	cmd1 = malloc(sizeof(t_cmd));
 	cmd1->args = char2_dup(arg1);
 	cmd1->input = 0;
 	cmd1->output = 1;
 	cmd1->input_type = INFILE;
 	cmd1->output_type = PIPE;
 	cmd1->infile = ft_strdup("depart");
 	cmd1->outfile = NULL;

 	t_cmd	*cmd2;
 	char	*arg2[] = {"grep", "-o", "robot", NULL};

 	cmd2 = malloc(sizeof(t_cmd));
 	cmd2->args = char2_dup(arg2);
 	cmd2->input = 0;
 	cmd2->output = 1;
 	cmd2->input_type = PIPE;
 	cmd2->output_type = PIPE;
 	cmd2->infile = NULL;
 	cmd2->outfile = NULL;

 	t_cmd	*cmd3;
 	char	*arg3[] = {"grep", "-o", "r", NULL};

 	cmd3 = malloc(sizeof(t_cmd));
 	cmd3->args = char2_dup(arg3);
 	cmd3->input = 0;
 	cmd3->output = 1;
 	cmd3->input_type = PIPE;
 	cmd3->output_type = REPLACE;
 	cmd3->infile = NULL;
 	cmd3->outfile = ft_strdup("fin");

 	cmd1->next = cmd2;
 	cmd1->prev = NULL;
 	cmd2->next = cmd3;
 	cmd2->prev = cmd1;
 	cmd3->next = NULL;
 	cmd3->prev = cmd2;

	int status = 0;
 	exec_all_cmd(cmd1, env, &status);
	printf("%i\n", status >> 8);

 	free_shell(env, cmd1);
 	return(0);
}
