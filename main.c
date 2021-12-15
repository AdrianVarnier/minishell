#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
	add_to_env(NULL, NULL, &env);
	add_to_env("PWD", getenv("PWD"), &env);
	add_to_env("OLDPWD", getenv("OLDPWD"), &env);
	add_to_env("HOME", getenv("HOME"), &env);
	
	char	*arg[] = {"export", "Test=this is a test", "Password=TEST", "TRICKY=TOWER", "EUUH=bahh", NULL};
	char	*un[] = {"unset", "Test", "TRICKY", "EUUH", NULL};

	ft_export(arg, &env);
	ft_env(env);
	ft_unset(un, env);
	ft_env(env);
	
	return(0);
}
