/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:18:03 by ali               #+#    #+#             */
/*   Updated: 2022/01/27 13:53:54 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_line(t_cmd *cmd, t_env *env)
{
	t_cmd	*to_free;

//	ft_print_cmd(cmd);
	to_free = cmd;
	g_exit = 0;
	exec_all_cmd(cmd, env);
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
			ft_signal(2);
			cmd = ft_parse_line(ret, &env);
			if (cmd)
				ft_exec_line(cmd, env);
			ft_signal(1);
			wait(NULL);
		}
		ret = readline("minishell>$");
	}
}
