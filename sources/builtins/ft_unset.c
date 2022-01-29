/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:35:32 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/29 22:36:14 by avarnier         ###   ########.fr       */
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
	if (tmp1 == NULL && tmp2 == NULL)
		*env = NULL;
	else if (tmp1 != NULL)
		*env = first_env(tmp1);
	else if (tmp2 != NULL)
		*env = first_env(tmp2);
}

int	ft_unset(char **arg, t_env **env)
{
	int		i;
	int		ret;
	t_env	*tmp;

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
					tmp = *env;
					break ;
				}
				tmp = *env;
				*env = (*env)->next;
			}
		}
		*env = first_env(tmp);
		i++;
	}
	return (ret);
}
