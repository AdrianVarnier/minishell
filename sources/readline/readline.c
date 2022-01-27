/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:18:03 by ali               #+#    #+#             */
/*   Updated: 2022/01/27 15:12:26 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_line(t_cmd *cmd, t_env *env)
{
	t_cmd	*to_free;

	to_free = cmd;
	exec_all_cmd(cmd, env);
	if (g_exit == 131)
	{
		write(1, "Quit (core dumped)", 18);
		rl_replace_line("", 1);
		write(1, "\n", 1);
		rl_on_new_line();
	}
	free_cmd(to_free);
}

void	ft_readline(t_env *env)
{
	t_cmd	*cmd;
	char	*ret;

	ret = readline("minishell>$");
	while (ret)
	{
		add_history(ret);
		if (ret[0])
		{
			cmd = ft_parse_line(ret, &env);
			if (cmd)
				ft_exec_line(cmd, env);
			wait(NULL);
		}
		ret = readline("minishell>$");
	}
}
