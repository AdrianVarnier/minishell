/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 20:11:32 by ali               #+#    #+#             */
/*   Updated: 2022/01/26 20:14:33 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_unquoted_var(char *line, t_env **env)
{
	int		i;
	char	c;

	i = 0;
	while (str[i])
	{
		if (str[i] =='\'' || str[i] == '\"')
		{
			c = str[i];
			i++;
			while (str[i] && str[i] != c)
				i++;
		}
		if (str[i])
			i++;
		if (ft_is_variable(&str[i]))
			str = ft_replace_unquote(strs, env);
		if (str[i])
			i++;
	}
}
