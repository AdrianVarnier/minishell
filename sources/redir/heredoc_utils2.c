/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 16:47:46 by ali               #+#    #+#             */
/*   Updated: 2022/02/02 02:35:24 by ali              ###   ########.fr       */
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

char	*get_heredoc_name(void)
{
	int		nb;
	int		loop;
	char	*name;
	char	*num;

	loop = 1;
	nb = 0;
	while (loop == 1)
	{
		num = ft_itoa(nb);
		name = ft_strjoin("heredoc_", num);
		free(num);
		if (access(name, F_OK) != 0)
			loop = 0;
		else
		{
			nb++;
			free(name);
		}
	}
	return (name);
}
