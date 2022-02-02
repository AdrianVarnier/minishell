/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ali <ali@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:51:33 by ali               #+#    #+#             */
/*   Updated: 2022/02/02 16:13:17 by ali              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd(t_cmd *cmd)
{
	char	**args;
	t_file	*infile;
	t_file	*outfile;

	while (cmd)
	{
		args = cmd->args;
		infile = cmd->infile;
		outfile = cmd->outfile;
		printf("ARGS :\n");
		while (*args)
		{
			printf("%s\n", *args);
			args++;
		}
		printf("\nINFILES :\n");
		while (infile)
		{
			printf("%s (type = %d)\n", infile->name, infile->type);
			infile = infile->next;
		}
		printf("\nOUTFILES :\n");
		while (outfile)
		{
			printf("%s (type = %d)\n", outfile->name, outfile->type);
			outfile = outfile->next;
		}
		printf("\n");
		cmd = cmd->next;
	}
}
