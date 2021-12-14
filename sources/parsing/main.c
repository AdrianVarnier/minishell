/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:51:33 by ali               #+#    #+#             */
/*   Updated: 2021/12/14 18:37:44 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	char		*ret;
	char		**strs;
	t_cmd		*cmds;
	int			i;
	int			j;
	t_env		*env = NULL;

	ret = readline("prompt>");
	while (ret)
	{
		add_history(ret);
		strs = ft_splitline(ret);
		add_to_env("TEST", "blubiblub", &env);
		add_to_env("TEST2", "crouchcrouch", &env);
		add_to_env("TEST3", "nenenenene nenenen", &env);
		ft_variables(strs, &env);
		if (ft_parse_error(strs))
			break ;
		cmds = ft_stock_cmd(strs);
		i = 0;
		while (strs[i])
		{
			printf("%s\n", strs[i]);
			i++;
		}
		while (cmds)
		{
			printf("\nCMD\n");
			i = 0;
			while (cmds->args[i])
			{
				printf("arg:%s\n", cmds->args[i]);
				i++;
			}
			cmds = cmds->next;
		}
		free(ret);
		ret = readline("prompt>");
	}
}


