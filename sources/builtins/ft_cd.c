/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:27:50 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 17:40:05 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *path)
{
	char *err_msg;

	if (access(path, F_OK) == -1)
	{
		err_msg = ft_strjoin3("minishell: cd: ", path, ": No such file or directory\n");
		ft_putstr_fd(err_msg, 2);
		free(err_msg);
		return(-1);
	}
	else if (access(path, X_OK) == -1)
	{
		err_msg = ft_strjoin3("minishell: cd: ", path, ": Permission denied\n");
		ft_putstr_fd(err_msg, 2);
		free(err_msg);
		return (-1);
	}
	return (0);
}

void	ft_cd_home(t_env *env)
{
	char	*path;

	path = get_env("HOME");
	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n");
		return ;
	}
	ft_cd(path, env);
}

void	ft_cd_oldpwd(t_env *env)
{
	char	*path;

	path = get_env("OLDPWD", env);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return ;
	}
	ft_cd(path, env);
}

void	ft_cd_here(t_env *env)
{
	char	new_path[PATH_MAX];

	getcwd(new_path,PATH_MAX);
	if (is_in_env("OLDPWD", env) == 0)
		add_to_env("OLDPWD", new_path, env);
	else
		set_env("OLDPWD", new_path, env);
}

void	ft_cd(char *path, t_env *env)
{
	char	new_path[PATH_MAX];
	char	old_path[PATH_MAX];

	if (check_path(path) == -1)
		return ;
	getcwd(old_path, PATH_MAX);
	if (chdir(path) == -1)
		return ;
	getcwd(new_path, PATH_MAX);
	if (is_in_env("PWD", env) == 0)
		add_to_env("PWD", new_path, env);
	else
		set_env("PWD", new_path, env);
	if (is_in_env("OLDPWD", env) == 0)
		add_to_env("OLDPWD", old_path, env);
	else
		set_env("OLDPWD", old_path, env);
}
