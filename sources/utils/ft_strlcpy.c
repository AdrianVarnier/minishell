/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 17:06:00 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/10 17:06:36 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlcpy(char *dst, char *src, int len)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < len)
		ft_memcpy(dst, src, srclen + 1);
	else if (len != 0)
	{
		ft_memcpy(dst, src, len - 1);
		dst[len - 1] = '\0';
	}
	return (srclen);
}
