/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 13:06:23 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/16 12:37:35 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s)
{
	int		i;
	int		len;
	char	*cpy;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s) + 1;
	cpy = malloc(sizeof(char) * len);
	if (cpy == NULL)
		return (NULL);
	ft_memcpy(cpy, s, len);
	return (cpy);
}
