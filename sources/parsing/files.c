/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:44:05 by ali               #+#    #+#             */
/*   Updated: 2021/12/28 19:02:55 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_output_type(t_cmd *cmd, char **strs)
{
	int	i;
	
	i = 0;
	while (strs[i] && !ft_is_separator(strs[i][0]))
		i++;
	if (!strs[i])
		cmd->output_type = 0;
	else if (strs[i][0] == '>' && !strs[i][1])
	{
		cmd->output_type = REPLACE;
		cmd->outfile = ft_strdup(strs[i + 1]);
	}
	else if (strs[i][0] == '>' && strs[i][1] == '>')
	{
		cmd->output_type = APPEND;
		cmd->outfile = ft_strdup(strs[i + 1]);
	}
	else if (strs[i][0] == '|')
		cmd->output_type = PIPE;
}

void	ft_input_type(t_cmd *cmd, char **strs, int index)
{
	int	i;

	i = 0;
	if (index == 0)
		cmd->input_type = 0;
	else if (strs[i - 1][0] == '|')
		cmd->input_type = PIPE;
	else if (index > 1 && strs[i - 2][0] == '<' && !strs[i - 2][1])
	{
		cmd->input_type = INFILE;
		cmd->infile = ft_strdup(strs[i - 1]);
	}
	else if (index > 1 && strs[i - 2][0] == '<' && strs[i - 2][1] == '<')
	{
		cmd->input_type = HEREDOC;
		cmd->infile = ft_strdup(strs[i - 1]);
	}
}

int		ft_filetype(t_cmd *cmd, char **strs, int index)
{
	int	i;

	i = 0;
	while (cmd->next != NULL)
		cmd = cmd->next;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	ft_output_type(cmd, strs);
	ft_input_type(cmd, strs, index);
	while (strs[i] && !ft_is_separator(strs[i][0]))
		i++;
	return (i);
}
