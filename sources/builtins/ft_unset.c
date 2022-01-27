/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:35:32 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/27 12:01:34 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*first_env(t_env *env)
{
	while (env->prev != NULL)
		env = env->prev;
	return (env);
}

static void	del_from_env(t_env **env)
{
	t_env	*tmp1;
	t_env	*tmp2;

	tmp1 = (*env)->prev;
	tmp2 = (*env)->next;
	if (tmp1 != NULL)
		tmp1->next = tmp2;
	if (tmp2 != NULL)
		tmp2->prev = tmp1;
	free((*env)->key);
	free((*env)->value);
	free(*env);
	while (tmp2->prev != NULL)
		tmp2 = tmp2->prev;
	*env = tmp2;
}

int	ft_unset(char **arg, t_env **env)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (arg[i] != NULL)
	{
		if (check_invalid(arg[i], 2) == 1)
			ret = 1;
		else
		{
			while (*env != NULL)
			{
				if (ft_strcmp(arg[i], (*env)->key) == 0)
				{
					del_from_env(env);
					break ;
				}
				*env = (*env)->next;
			}
		}
		*env = first_env(*env);
		i++;
	}
	return (ret);
}
