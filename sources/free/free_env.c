/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 12:25:29 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/16 16:33:18 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env->prev != NULL)
		env = env->prev;
	while (env != NULL)
	{
		tmp = env->next;
		if (env->key != NULL)
			free(env->key);
		if (env->value != NULL)
			free(env->value);
		free(env);
		env = tmp;
	}
}
