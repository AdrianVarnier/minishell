/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:06:23 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 13:07:09 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*cpy;

	i = 0;
	len = ft_strlen(s) + 1;
	if (!(cpy = (char *)malloc(sizeof(char) * len)))
		return (0);
	ft_memcpy(cpy, s, len);
	return (cpy);
}
