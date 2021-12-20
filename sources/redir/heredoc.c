/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:18:25 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/20 22:59:20 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_dup(char *s)
{
	int		i;
	int		len;
	char	*cpy;

	if (s == NULL)
		return (NULL);
	i = 0;
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
	int		*fd;
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
		free_shell(env, cmd);
		exit(0);
	}
	close(fd[1]);
}

void	create_heredoc(t_cmd *cmd, t_env *env)
{
	char	*line;
	char	*heredoc;

	heredoc = NULL;
	if (cmd->input_type != HEREDOC)
		return ;
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, cmd->infile) == 0)
		{
			free(line);
			break ;
		}
		heredoc = ft_join(heredoc, line);
		free(line);
		line = readline("> ");
	}
	send_heredoc(heredoc, cmd, env);
}
