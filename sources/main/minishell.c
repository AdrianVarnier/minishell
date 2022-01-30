/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 16:38:12 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/30 06:15:02 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit;

void	ft_up_shlvl(t_env *env)
{
	int	lvl;

	lvl = ft_atoi(get_env("SHLVL", env));
	lvl++;
	set_env("SHLVL", ft_itoa(lvl), env);
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
