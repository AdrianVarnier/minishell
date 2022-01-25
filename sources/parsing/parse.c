/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:41:58 by ali               #+#    #+#             */
/*   Updated: 2022/01/25 00:50:49 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_line(char *line, t_env **env)
{
	char	**strs;
	t_cmd	*cmd;
	char	*exit;

	cmd = NULL;
	strs = ft_splitline(line);
	if (ft_parse_error(strs))
	{
		free_char2(strs);
		return (NULL);
	}
	exit = ft_itoa(g_exit);
	if (!get_env("?", *env))
		add_to_env("?", exit, env);
	else
		set_env("?", exit, *env);
	free(exit);
	ft_variables(strs, env);
	ft_quotes(strs);
	cmd = ft_stock_cmd(strs);
	free_char2(strs);
	return (cmd);
}
