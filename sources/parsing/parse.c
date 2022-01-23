/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:41:58 by ali               #+#    #+#             */
/*   Updated: 2022/01/23 15:31:35 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*ft_parse_line(char *line, t_env **env)
{
	char	**strs;
	t_cmd	*cmd;

	cmd = NULL;
	strs = ft_splitline(line);
	if (ft_parse_error(strs))
	{
		free_char2(strs);
		return (NULL);
	}
	if (!get_env("?", *env))
		add_to_env("?", ft_itoa(g_exit), env);
	else
		set_env("?", ft_itoa(g_exit), *env);
	ft_variables(strs, env);
	cmd = ft_stock_cmd(strs);
	free_char2(strs);
	return (cmd);
}
