/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:38:12 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/26 22:13:29 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void) ac;
	(void) av;
	env = NULL;
	g_exit = 0;
	env = ft_parse_env(envp);
	add_to_env("?", "0", &env);
	ft_readline(env);
	free_env(env);
}
