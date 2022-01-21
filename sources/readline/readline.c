/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:18:03 by ali               #+#    #+#             */
/*   Updated: 2022/01/21 15:39:39 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_readline(t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*to_free;
	char	*ret;

	signal(SIGQUIT, ft_handler);
	signal(SIGINT, ft_handler);
	ret = readline("minishell>$");
	while (ret)
	{
		add_history(ret);
		if (ret[0])
		{
			signal(SIGQUIT, ft_handler2);
			signal(SIGINT, ft_handler2);
			cmd = ft_parse_line(ret, &env);
			ft_print_cmd(cmd);
			to_free = cmd;
			//exec_all_cmd(cmd, env);
			free(ret);
			free_cmd(to_free);
			signal(SIGQUIT, ft_handler);
			signal(SIGINT, ft_handler);
		}
		ret = readline("minishell>$");
	}
}
