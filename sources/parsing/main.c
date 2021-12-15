/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:51:33 by ali               #+#    #+#             */
/*   Updated: 2021/12/15 18:05:29 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(void)
{
	char		*ret;
	t_cmd		*cmds;
	int			i;
	t_env		*env = NULL;

	ret = readline("prompt>");
	while (ret)
	{
		add_history(ret);
		add_to_env("TEST", "blubiblub", &env);
		add_to_env("TEST2", "crouchcrouch", &env);
		add_to_env("TEST3", "nenenenene nenenen", &env);
		cmds = ft_parse_line(ret, &env);
		while (cmds)
		{
			printf("\nCMD\n");
			i = 0;
			while (cmds->args[i])
			{
				printf("arg:%s\n", cmds->args[i]);
				i++;
			}
			printf("infile = %s\noutfile = %s\n", cmds->infile, cmds->outfile);
			cmds = cmds->next;
		}
		free(ret);
		ret = readline("prompt>");
	}
}


