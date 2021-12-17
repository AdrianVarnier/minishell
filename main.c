#include "minishell.h"

int main(int argc, char **argv, char **envp)
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
		fprintf(stderr, "%s %s %s %i\n", cmd->args[0], cmd->args[1], cmd->infile, cmd->input_type);
		fprintf(stderr, "%s %s %i\n", cmd->next->args[0], cmd->next->args[1], cmd->next->output_type);
//		exec_all_cmd(cmd, env);
		free_cmd(cmd);
		free(line);
		line = readline("minishell: ");
	}
	
	return(0);
}
