/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:27:15 by ali               #+#    #+#             */
/*   Updated: 2021/12/16 15:32:56 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_parse_env(char **envp)
{
	t_env	*env;
	int		i;

	i = 0;
	while (envp[i])
	{
		add_to_env(ft_get_key(envp[i]), ft_get_value(envp[i], &env));
		i++;
	}
	return (env);
}
