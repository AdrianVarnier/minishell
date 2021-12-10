/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:59:13 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 18:03:42 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_env(char *name, char *content, t_env *env)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return ;
	while (env->next != NULL)
		env = env->next;
	new->next = NULL;
	new->prev = env;
	new->key = ft_strdup(name);
	new->value = ft_strdup(content);
	env->next = new;
}
