/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:41:58 by ali               #+#    #+#             */
/*   Updated: 2022/02/03 11:07:46 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_variable_error(char *str)
{
	int	i;

	i = 1;
	if (str[i] != '{')
		return (0);
	i++;
	while (str[i] && str[i] != '}')
	{
		if (ft_is_vardel(str[i], " \'\"\\][@$&*().|><"))
			return (1);
		i++;
	}
	if (!str[i])
		return (1);
	return (0);
}

int	ft_variable_error(char *str)
{
	int		i;
	int		simple;

	simple = 1;
	i = 0;
	while (str[i])
	{
		while (str[i] && !ft_is_variable(&str[i]))
		{
			if (str[i] == '\'')
				simple *= -1;
			i++;
		}
		if (str[i] && simple == 1)
		{
			if (ft_check_variable_error(&str[i]))
			{
				ft_putendl_fd("minishell: syntax error", 2);
				return (1);
			}
		}
		if (str[i])
			i++;
	}
	return (0);
}

t_cmd	*ft_exit_parse(char **strs)
{
	g_exit = 2;
	free_char2(strs);
	return (NULL);
}

t_cmd	*ft_parse_line(char *line, t_env **env)
{
	char	**strs;
	t_cmd	*cmd;
	char	*exit;

	cmd = NULL;
	exit = ft_itoa(g_exit);
	set_env("?", exit, *env);
	free(exit);
	if (ft_variable_error(line))
	{
		free(line);
		return (NULL);
	}
	line = ft_variables_heredoc(line);
	strs = ft_splitline(line);
	free(line);
	if (ft_parse_error(strs))
		return (ft_exit_parse(strs));
	ft_variables(strs, env);
	ft_quotes(strs);
	cmd = ft_stock_cmd(strs);
	free_char2(strs);
	return (cmd);
}
