/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:37:05 by ali               #+#    #+#             */
/*   Updated: 2021/12/16 15:56:24 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_readline(t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*to_free;
	char	*ret;

	ret = readline("minishell>$");
	while (ret)
	{
		add_history(ret);
		cmd = ft_parse_line(ret, &env);
		to_free = cmd;
		exec_cmd(cmd, env);
		free(ret);
		free_cmd(to_free);
		ret = readline("minishell>$");
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	env = NULL;
	env = ft_parse_env(envp);
	ft_readline(env);
	free_env(env);
}
