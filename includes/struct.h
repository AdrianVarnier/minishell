/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 12:10:49 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/17 13:07:55 by avarnier         ###   ########.fr       */
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
	pid_t	pid;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}		t_cmd;

#endif
