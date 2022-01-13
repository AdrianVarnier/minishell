/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:55:49 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/13 16:39:14 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	send_err_msg(char *name, char mode)
{
	char	*err_msg;

	if (mode == 'F')
		err_msg = ft_strjoin3("minishell: ", name, ": No such file or directory");
	if (mode == 'R')
		err_msg = ft_strjoin3("minishell: ", name, ": Read permission denied");
	if (mode == 'W')
		err_msg = ft_strjoin3("minishell: ", name, ": Write permission denied");
	if (mode == 'O')
		err_msg = ft_strjoin3("minishell: ", name, ": Open failure");
	if (err_msg != NULL)
	{
		ft_putendl_fd(err_msg, 2);
		free(err_msg);
	}
}

static int	check_infile(t_file *infile, t_cmd *cmd)
{
	int	fd;

	if (access(infile->name, F_OK) == -1)
	{
		send_err_msg(infile->name, 'F');
		return (0);
	}
	if (access(infile->name, R_OK) == -1)
	{
		send_err_msg(infile->name, 'R');
		return (0);
	}
	fd = open(infile->name, O_RDONLY);
	if (fd == -1)
	{
		send_err_msg(infile->name, 'O');
		return (0);
	}
	if (infile->next == NULL)
		cmd->input = fd;
	else
		close(fd);
	return (1);
}

static int	check_outfile(t_file *outfile, t_cmd *cmd)
{
	int	fd;

	if (access(outfile->name, F_OK) == 0)
	{
		if (access(outfile->name, W_OK) == -1)
		{
			send_err_msg(outfile->name, 'W');
			return (0);
		}
	}
	if (outfile->type == APPEND)
		fd = open(outfile->name, O_WRONLY | O_APPEND | O_CREAT);
	if (outfile->type == REPLACE)
		fd = open(outfile->name, O_WRONLY | O_TRUNC | O_CREAT);
	if (fd == -1)
	{
		send_err_msg(outfile->name, 'O');
		return (0);
	}
	if (outfile->next == NULL)
		cmd->output = fd;
	else
		close(fd);
	return (1);
}

static int	check_all(t_file *infile, t_file *outfile, t_cmd *cmd)
{
	while (infile != NULL)
	{
		if (infile->type != HEREDOC && infile->type != PIPE)
			if (check_infile(infile, cmd) == 0)
				return (0);
		infile = infile->next;
	}
	while (outfile != NULL)
	{
		if (outfile->type != HEREDOC && outfile->type != PIPE)
			if (check_outfile(outfile, cmd) == 0)
				return (0);
		outfile = outfile->next;
	}
	return (1);
}

int	check_file(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (check_all(cmd->infile, cmd->outfile, cmd) == 0)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}
