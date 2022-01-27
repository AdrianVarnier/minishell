/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 08:14:07 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/27 11:58:00 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_name(char *s)
{
	int		i;
	char	*name;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (name == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		name[i] = s[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

static void	send_err_msg(char *s, int mode)
{
	char	*name;
	char	*err_msg;

	name = get_name(s);
	if (mode == 1)
		err_msg = ft_strjoin3("minishell: export: ",
				name, ": not a valid identifier");
	if (mode == 2)
		err_msg = ft_strjoin3("minishell: unset: ",
				name, ": not a valid identifier");
	ft_putendl_fd(err_msg, 2);
	free(name);
	free(err_msg);
}

int	check_invalid(char *s, int mode)
{
	int	i;

	i = 0;
	if (!((s[0] <= 'z' && s[0] >= 'a') || (s[0] <= 'Z' && s[0] >= 'A')
			|| s[0] == '_'))
	{
		send_err_msg(s, mode);
		return (1);
	}
	while (s[i] != '\0' && s[i] != '=')
	{
		if (!((s[0] <= 'z' && s[0] >= 'a') || (s[0] <= 'Z' && s[0] >= 'A')
				|| (s[i] <= '9' && s[i] >= '0') || s[0] == '_'))
		{
			send_err_msg(s, mode);
			return (1);
		}
		i++;
	}
	return (0);
}
