/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:47:46 by ali               #+#    #+#             */
/*   Updated: 2022/02/01 16:49:41 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_read_heredoc(t_file *infile, int *fd)
{
	char	*heredoc;

	ft_signal(3);
	close(fd[0]);
	heredoc = ft_read_heredoc(infile);
	write(fd[1], heredoc, ft_strlen(heredoc));
	close(fd[1]);
	exit (0);
}
