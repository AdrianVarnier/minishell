/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:25:38 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 17:32:08 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	while(env != NULL)
	{
		ft_putstr_fd(env->key, 0);
		ft_putstr_fd("=", 0);
		ft_putstr_fd(env->value, 0);
		ft_putstr_fd("\n", 0);
		env = env->next;
	}
}
