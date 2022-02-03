/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   already_open.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:21:57 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/03 18:36:02 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	already_open_file(t_file *file, char *name, int mode)
{
	while (file != NULL)
	{
		if (file->type == INFILE && mode == 1)
			if (ft_strcmp(name, file->name) == 0 && access(name, F_OK) == 0 && file->fd != 0)
				return (1);
		if ((file->type == APPEND || file->type == REPLACE) && mode == 2)
			if (ft_strcmp(name, file->name) == 0 && access(name, F_OK) == 0 && file->fd != 0)
				return (1);
		file = file->next;
	}
	return (0);
}

int	already_open(t_cmd *cmd, char *name, int mode)
{
	while (cmd != NULL)
	{
		if (cmd->outfile != NULL)
			if (already_open_file(cmd->outfile, name, mode) == 1 && mode == 1)
				return (1);
		if (cmd->infile != NULL)
			if (already_open_file(cmd->infile, name, mode) == 1 && mode == 2)
				return (1);
		cmd = cmd->prev;
	}
	return (0);
}

static int	get_file_fd(t_file *file, char *name)
{
	while (file != NULL)
	{
		if (file->type == APPEND || file->type == REPLACE || file->type == INFILE)
			if (ft_strcmp(name, file->name) == 0)
				return (file->fd);
		file = file->next;
	}
	return (0);
}

int	get_fd(t_cmd *cmd, char *name, int mode)
{
	while (cmd != NULL)
	{
		if (already_open_file(cmd->infile, name, mode) == 1 && mode == 1)
				return (get_file_fd(cmd->infile, name));
		if (already_open_file(cmd->outfile, name, mode) == 1 && mode == 2)
				return (get_file_fd(cmd->outfile, name));
		cmd = cmd->prev;
	}
	return (0);
}
