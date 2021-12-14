/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:10:49 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/14 15:19:03 by ali              ###   ########.fr       */
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
	char	**args;
	int		input;
	int		output;
	int		input_type;
	int		output_type;
	char	*infile;
	char	*outfile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_cmd;

typedef struct s_shell
{
	struct s_env	*env;
	struct s_cmd	*cmd;
}		t_shell;

#endif
