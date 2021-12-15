/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:11:56 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/15 17:55:34 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
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
char	**env_to_char2(t_env *env);

//exec

int	is_builtin(char *name);
int	is_supported(char *name, char *option);
void	exec_builtin(t_cmd *cmd, t_env *env, t_shell *shell);
void	exec_cmd(t_cmd *cmd, t_env *env, t_shell *shell);
char	**env_to_char2(t_env *env);
char	**cmd_to_char2(t_cmd *cmd);
void	create_pipe(t_cmd *cmd, t_env *env, t_shell *shell);
void	redir_pipe(t_cmd *cmd);

//free

void	free_env(t_env *env);
void	free_cmd(t_cmd *cmd);
void	free_shell(t_shell *shell);
void	free_char2(char **to_free);

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
char	*ft_strjoin3(char *s1, char *s2, char *s3);
char	*ft_strjoin5(char *s1,char *s2, char *s3, char *s4, char *s5);
char	**ft_split(char *s, char c);

//parsing

void	ft_add_cmd(t_cmd **cmd, char **strs);
int		ft_next_cmd(char **strs);
t_cmd	*ft_stock_cmd(char **strs);
int	ft_is_file(char **strs, int index);
void	ft_place_cmd(t_cmd **cmd, t_cmd *new);
void	ft_output_type(t_cmd *cmd, char **strs);
void	ft_input_type(t_cmd *cmd, char **strs, int index);
int		ft_filetype(t_cmd *cmd, char **strs, int index);
int	ft_end_error(char **strs);
int	ft_pipe_nocmd(char **strs);
int	ft_conjoin_error(char **strs);
int	ft_parse_error(char **strs);
int	ft_quote_closed(char *str);
char	*ft_remove_quote(char *str);
int	ft_count_words_line(char *str);
int	ft_wordlen_line(char *str);
char	*ft_copy_word(char *str);
void	ft_fill(char **strs, char *str, int size);
char	**ft_splitline(char *str);
int	ft_is_separator(char c);
int	ft_pass_sep(char *str);
int	ft_next_word(char *str);
int	ft_pass_quote(char *str);
int	ft_pass_word(char *str);
int	ft_size_sub(char *str, t_env **env);
int	ft_sub(char *sub, char *str, t_env **env);
void	ft_fill_sub(char *str, char *sub, int size, t_env **env);
char	*ft_replace(char *str, t_env **env);
void	ft_variables(char **strs, t_env **env);
int		ft_strcmp(char *s1, char *s2);
char	*ft_get_varname(char *str);
char	*ft_get_var(char *str, t_env **env);
int	ft_variable_size(char *str, t_env **env);
int	ft_pass_variable(char *str);
t_cmd	*ft_parse_line(char *line, t_env **env);

#endif
