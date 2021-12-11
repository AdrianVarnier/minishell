/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:11:56 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 12:50:56 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "define.h"
# include "struct.h"

//builtins

void	ft_pwd(void);
void	ft_cd(char *path, t_env *env);
void	ft_env(t_env *env);
void	ft_unset(char *name, t_env *env);
void	ft_export(char *s, t_env *env);

//env

char	*get_env(char *name, t_env *env);
void	set_env(char *name, char *content, t_env *env);
int	is_in_env(char *name, t_env *env);
t_env	*add_to_env(char *name, char *content, t_env *env);

//exec

int	is_builtin(char *name);
int	is_supported(char *name, char *option);

//free

void	free_env(t_env *env);
void	free_cmd(t_cmd *cmd);
void	free_shell(t_shell *shell);

//utils

int	ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
int	ft_strcmp(char *s1, char *s2);
void	*ft_memcpy(void *dst, void *src, int len);
char	*ft_strdup(char *s);
int	ft_strlcpy(char *dst, char *src, int len);
int	ft_strlcat(char *dst, char *src, int len);
char	*ft_strjoin3(char *s1, char *s2, char *s3);

#endif
