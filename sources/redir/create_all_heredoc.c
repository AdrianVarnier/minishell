/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_all_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:57:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/02/01 15:11:59 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_dup(char *s)
{
	int		len;
	char	*cpy;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) + 2;
	cpy = malloc(sizeof(char) * len);
	if (cpy == NULL)
		return (NULL);
	ft_strlcpy(cpy, s, ft_strlen(s) + 1);
	cpy[len - 2] = '\n';
	cpy[len - 1] = '\0';
	return (cpy);
}

static char	*ft_join(char *s1, char *s2)
{
	int		size;
	char	*new;

	if (s1 == NULL)
		return (ft_dup(s2));
	size = ft_strlen(s1) + ft_strlen(s2) + 2;
	new = malloc(sizeof(char) * size);
	if (new == NULL)
		return (s1);
	ft_strlcpy(new, s1, ft_strlen(s1) + 1);
	ft_strlcat(new, s2, ft_strlen(new) + ft_strlen(s2) + 1);
	new[size - 2] = '\n';
	new[size - 1] = '\0';
	return (new);
}

static void	send_heredoc(char *heredoc, t_file *infile)
{
	int			fd;
	static int	nb = 0;
	char		*num;
	char		*name;

	fd = 1;
	while (fd == 1)
	{
		num = ft_itoa(nb);
		name = ft_strjoin("heredoc_", num);
		free(num);
		if (access(name, F_OK) != 0)
			fd = 0;
		else
		{
			nb++;
			free(name);
		}
	}
	fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR
			| S_IRGRP | S_IROTH);
	write(fd, heredoc, ft_strlen(heredoc));
	close(fd);
	free(heredoc);
	free(infile->name);
	infile->name = ft_strdup(name);
	free(name);
	nb++;
}

static void	create_heredoc(t_file *infile, int mode)
{
	char	*line;
	char	*heredoc;
	char	*tmp;

	heredoc = NULL;
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, infile->name) == 0)
		{
			free(line);
			break ;
		}
		tmp = ft_join(heredoc, line);
		free(heredoc);
		heredoc = tmp;
		free(line);
		line = readline("> ");
	}
	if (mode == 1)
		send_heredoc(heredoc, infile);
	else
		free(heredoc);
}

void	create_all_heredoc(t_file *infile)
{
	while (infile != NULL)
	{
		if (infile->type == HEREDOC && infile->next == NULL)
			create_heredoc(infile, 1);
		else if (infile->next != NULL)
		{
			if (infile->type == HEREDOC && infile->next->type == PIPE)
				create_heredoc(infile, 1);
			else if (infile->type == HEREDOC && (infile->next->type == HEREDOC
					|| infile->next->type == INFILE))
				create_heredoc(infile, 0);
		}
		infile = infile->next;
	}
}
