/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:55:49 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/20 22:48:56 by avarnier         ###   ########.fr       */
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

static int	check_infile(char *infile, t_cmd *cmd)
{
	int	fd;

	if (access(infile, F_OK) == -1)
	{
		send_err_msg(infile, 'F');
		return (0);
	}
	if (access(infile, R_OK) == -1)
	{
		send_err_msg(infile, 'R');
		return (0);
	}
	fd = open(infile, O_RDONLY);
	if (fd == -1)
	{
		send_err_msg(infile, 'O');
		return (0);
	}
	cmd->input = fd;
	return (1);
}

static int	check_outfile(char *outfile, t_cmd *cmd)
{
	int	fd;

	if (access(outfile, F_OK) == 0)
	{
		if (access(outfile, W_OK) == -1)
		{
			send_err_msg(outfile, 'W');
			return (0);
		}
	}
	if (cmd->output_type == APPEND)
		fd = open(outfile, O_WRONLY | O_APPEND | O_CREAT);
	if (cmd->output_type == REPLACE)
		fd = open(outfile, O_WRONLY | O_TRUNC | O_CREAT);
	if (fd == -1)
	{
		send_err_msg(outfile, 'O');
		return (0);
	}
	cmd->output = fd;
	return (1);
}

int	check_file(t_cmd *cmd)
{
	while (cmd != NULL)
	{
		if (cmd->infile != NULL && cmd->input_type != HEREDOC)
			if (check_infile(cmd->infile, cmd) == 0)
				return (0);
		if (cmd->outfile != NULL && cmd->output_type != HEREDOC)
			if (check_outfile(cmd->outfile, cmd) == 0)
				return (0);
		cmd = cmd->next;
	}
	return (1);
}
