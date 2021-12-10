/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:11:56 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 13:16:02 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include "define.h"
# include "struct.h"

//builtins

void	pwd(void);

//env

char	*get_env(char *name, t_env *env);
void	set_env(char *name, char *content, t_env *env);

//utils

int	ft_strlen(char *s);
void	ft_putstr_fd(char *s, int fd);
int	ft_strcmp(char *s1, char *s2);
void	*ft_memcpy(void *dst, void *src, int len);
char	*ft_strdup(char *s);

#endif
