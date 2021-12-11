/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_back.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:40:37 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 23:39:55 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_path_size(char *path)
{
	int	i;

	i = ft_strlen(path);
	while (i >= 0)
	{
		if (path[i] == '/')
			return (i);
		i--;
	}
	return (ft_strlen(path));
}

static char	*get_back_path(char *old_path)
{
	int	i;
	char	*new_path;

	i = get_path_size(old_path);
	new_path = (char *)malloc(sizeof(char) * (i + 1));
	new_path[i] = '\0';
	i--;
	while (i >= 0)
	{
		new_path[i] = old_path[i];
		i--;
	}
	return (new_path);
}

void	ft_cd_back(t_env *env)
{
	char	old_path[PATH_MAX];
	char	*new_path;

	getcwd(old_path, PATH_MAX);
	new_path = get_back_path(old_path);
	ft_cd(new_path, &env);
	free(new_path);
}
