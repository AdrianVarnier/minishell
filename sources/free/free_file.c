/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 17:07:43 by avarnier          #+#    #+#             */
/*   Updated: 2022/01/12 17:10:00 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_file(t_file *file)
{
	t_file	*tmp;

	while (file != NULL)
	{
		tmp = file->next;
		free(file->name);
		free(file);
		file = tmp;
	}
}
