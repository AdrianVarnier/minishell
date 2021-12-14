/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:44:05 by ali               #+#    #+#             */
/*   Updated: 2021/12/14 18:35:47 by ali              ###   ########.fr       */
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
		cmd->output_type = REPLACE;
	else if (strs[i][0] == '>' && strs[i][1] == '>')
		cmd->output_type = APPEND;
	else if (strs[i][0] == '|')
		cmd->output = PIPE;
}

void	ft_input_type(t_cmd *cmd, char **strs, int index)
{
	int	i;

	i = 0;
	if (index == 0)
		cmd->input = 0;
	else if (strs[i - 1][0] == '|')
		cmd->input = PIPE;
	else if (index > 1 && strs[i - 2][0] == '<' && !strs[i - 2][1])
		cmd->input = INFILE;
	else if (index > 1 && strs[i - 2][0] == '<' && !strs[i - 2][1] == '<')
		cmd->input = HEREDOC;
}

int		ft_filetype(t_cmd *cmd, char **strs, int index)
{
	int	i;

	i = 0;
	while (cmd->next != NULL)
		cmd = cmd->next;
	ft_output_type(cmd, strs);
	ft_input_type(cmd, strs, index);
	while (strs[i] && !ft_is_separator(strs[i][0]))
		i++;
	return (i);
}
