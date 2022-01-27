/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:07:43 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/27 06:59:22 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file(t_file *file)
{
	t_file	*tmp;

	while (file != NULL)
	{
		tmp = file->next;
		if (file->name != NULL)
			free(file->name);
		free(file);
		file = tmp;
	}
}
