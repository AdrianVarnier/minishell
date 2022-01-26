/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:35:32 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/26 15:44:41 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	*env = tmp2;
}

static int	err_msg(void)
{
	ft_putendl_fd("minishell: unset: ?: not a valid identifier", 2);
	return (1);
}

int	ft_unset(char **arg, t_env **env)
{
	int		i;

	i = 1;
	while (*env != NULL)
	{
		while (arg[i] != NULL)
		{
			if (ft_strcmp(arg[i], "?") == 0)
				return (err_msg());
			if (ft_strcmp(arg[i], (*env)->key) == 0)
			{
				del_from_env(env);
				break ;
			}
			i++;
		}
		i = 1;
		if (*env != NULL)
			*env = (*env)->next;
	}
	return (0);
}
