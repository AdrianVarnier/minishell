/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 14:59:13 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 15:03:05 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*new_env(char *name, char *content)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (NULL);
	env->next = NULL;
	env->prev = NULL;
	env->key = ft_strdup(name);
	env->value = ft_strdup(content);
	return (env);
}

t_env	*add_to_env(char *name, char *content, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	new = NULL;
	tmp = NULL;
	if (env == NULL)
		return (new_env(name, content));
	tmp = env;
	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (env);
	while (env->next != NULL)
		env = env->next;
	new->next = NULL;
	new->prev = env;
	new->key = ft_strdup(name);
	new->value = ft_strdup(content);
	env->next = new;
	return (tmp);
}
