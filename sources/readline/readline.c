/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:18:03 by ali               #+#    #+#             */
/*   Updated: 2022/01/20 18:29:32 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_readline(t_env *env)
{
	t_cmd	*cmd;
	t_cmd	*to_free;
	char	*ret;

	ft_signal();
	ret = readline("minishell>$");
	while (ret)
	{
		add_history(ret);
		if (ret[0])
		{
			g_line = 1;
			cmd = ft_parse_line(ret, &env);
			to_free = cmd;
			exec_all_cmd(cmd, env);
			free(ret);
			free_cmd(to_free);
			g_line = 0;
		}
		ret = readline("minishell>$");
	}
}
