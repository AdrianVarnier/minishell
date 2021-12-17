/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 12:18:03 by ali               #+#    #+#             */
/*   Updated: 2021/12/17 12:19:30 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_readline(t_env *env)
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
