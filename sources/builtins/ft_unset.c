/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:35:32 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 18:08:23 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char *name, t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	while (env != NULL)
	{
		if (ft_strcmp(name, env->key) == 0)
		{
			tmp1 = env->prev;
			tmp2 = env->next;
			if (tmp1 != NULL)
				tmp1->next = tmp2;
			if (tmp2 != NULL)
				tmp2->prev = tmp1;
			free(env->key);
			free(env->value);
			free(env);
			return ;
		}
		env = env->next;
	}
}
