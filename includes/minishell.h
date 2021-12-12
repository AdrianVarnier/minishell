/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:11:56 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/12 15:34:59 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "define.h"
# include "struct.h"

//builtins

void	ft_pwd(void);
void	ft_cd(char *path, t_env **env);
void	ft_cd_here(t_env *env);
void	ft_cd_oldpwd(t_env *env);
void	ft_cd_home(t_env *env);
void	ft_cd_back(t_env *env);
void	ft_env(t_env *env);
void	ft_unset(char *name, t_env *env);
void	ft_export(char *s, t_env **env);
void	ft_echo(char *s, int mode);

//env

char	*get_env(char *name, t_env *env);
void	set_env(char *name, char *content, t_env *env);
int	is_in_env(char *name, t_env *env);
void	add_to_env(char *name, char *content, t_env **env);

//exec

int	is_builtin(char *name);
int	is_supported(char *name, char *option);
void	exec_builtin(t_cmd *cmd, t_env *env);
void	exec_cmd(t_cmd *cmd, t_env *env, char **envp);

//free

void	free_env(t_env *env);
void	free_cmd(t_cmd *cmd);
void	free_shell(t_shell *shell);

//utils

int	ft_strlen(char *s);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
int	ft_strcmp(char *s1, char *s2);
void	*ft_memcpy(void *dst, void *src, int len);
char	*ft_strdup(char *s);
int	ft_strlcpy(char *dst, char *src, int len);
int	ft_strlcat(char *dst, char *src, int len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*ft_strjoin5(char *s1,char *s2, char *s3, char *s4, char *s5);
char	**ft_split(char *s, char c);

#endif
