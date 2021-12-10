/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:31:03 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 12:36:24 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env(char *name, t_env *env)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
