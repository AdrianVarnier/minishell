/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:38:12 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/31 12:28:35 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	ft_up_shlvl(t_env *env)
{
	int		lvl;
	char	*next_lvl;

	lvl = ft_atoi(get_env("SHLVL", env));
	lvl++;
	next_lvl = ft_itoa(lvl);
	set_env("SHLVL", next_lvl, env);
	free(next_lvl);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void) ac;
	(void) av;
	env = NULL;
	g_exit = 0;
	env = ft_parse_env(envp);
	add_to_env("?", "0", &env);
	ft_up_shlvl(env);
	ft_signal(1);
	ft_readline(&env);
	free_env(env);
	write(1, "exit\n", 5);
	exit(g_exit);
}
