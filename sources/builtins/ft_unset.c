/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:35:32 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/18 04:45:56 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **arg, t_env **env)
{
	int	i;
	t_env	*tmp1;
	t_env	*tmp2;

	i = 1;
	while (*env != NULL)
	{
		while (arg[i] != NULL)
		{
			if (ft_strcmp(arg[i], (*env)->key) == 0)
			{
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
				break ;
			}
			i++;
		}
		i = 1;
		if (*env != NULL)
			*env = (*env)->next;
	}
}
