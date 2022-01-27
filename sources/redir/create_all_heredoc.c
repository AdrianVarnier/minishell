/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_all_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 02:57:04 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/27 03:06:51 by avarnier         ###   ########.fr       */
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

static void	send_heredoc(char *heredoc, t_cmd *cmd, t_env *env)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	cmd->input = fd[0];
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		ft_putstr_fd(heredoc, STDOUT_FILENO);
		free(heredoc);
		free_shell(env, cmd);
		exit(0);
	}
	if (pid > 0)
		free(heredoc);
	waitpid(pid, NULL, 0);
	close(fd[1]);
}

static void	create_heredoc(t_cmd *cmd, t_file *infile, t_env *env, int mode)
{
	char	*line;
	char	*heredoc;

	heredoc = NULL;
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, infile->name) == 0)
		{
			free(line);
			break ;
		}
		heredoc = ft_join(heredoc, line);
		free(line);
		line = readline("> ");
	}
	if (mode == 1)
		send_heredoc(heredoc, cmd, env);
	else
		free(heredoc);
}

void	create_all_heredoc(t_cmd *cmd, t_file *infile, t_env *env)
{
	while (infile != NULL)
	{
		if (infile->type == HEREDOC && infile->next == NULL)
			create_heredoc(cmd, infile, env, 1);
		else if (infile->next != NULL)
		{
			if (infile->type == HEREDOC && infile->next->type == PIPE)
				create_heredoc(cmd, infile, env, 1);
			else if (infile->type == HEREDOC && (infile->next->type == HEREDOC || infile->next->type == INFILE))
				create_heredoc(cmd, infile, env, 0);
		}
		infile = infile->next;
	}
}
