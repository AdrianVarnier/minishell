/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:10:49 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/13 15:51:03 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct    s_env
{
    char		*key;
    char		*value;
    struct s_env	*next;
    struct s_env	*prev;
}   		t_env;

typedef struct	s_cmd
{
	char		*name;
	char		*option;
	char		*arg;
	int		input;
	int		output;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_cmd;

typedef struct s_shell
{
	struct s_env	*env;
	struct s_cmd	*cmd;
}		t_shell;

#endif
