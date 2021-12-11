/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 17:43:35 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/11 17:46:15 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin5(char *s1, char *s2, char *s3, char *s4, char *s5)
{
	int	i;
	char	*s;

	i = 0;
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
	+ ft_strlen(s3) + ft_strlen(s4) + ft_strlen(s5) + 1));
	if (s == NULL)
		return (NULL);
	ft_strlcpy(s, s1, ft_strlen(s1) + 1);
	ft_strlcat(s, s2, ft_strlen(s) + ft_strlen(s2) + 1);
	ft_strlcat(s, s3, ft_strlen(s) + ft_strlen(s3) + 1);
	ft_strlcat(s, s4, ft_strlen(s) + ft_strlen(s4) + 1);
	ft_strlcat(s, s5, ft_strlen(s) + ft_strlen(s5) + 1);
	return (s);
}
