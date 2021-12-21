/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avarnier <avarnier@stduent.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:30:55 by avarnier          #+#    #+#             */
/*   Updated: 2021/12/21 17:31:43 by avarnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_numbers(unsigned int n)
{
	int	counter;

	if (n == 0)
		return (1);
	counter = 0;
	while (n > 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

char			*ft_itoa(int n)
{
	int				i;
	unsigned int	nb;
	char			*s;

	if (n < 0)
		nb = -n;
	else
		nb = n;
	if (!(s = (char *)malloc((sizeof(char) *
	(ft_numbers(nb) + 1 + (n < 0 ? 1 : 0))))))
		return (0);
	i = ft_numbers(nb) - 1 + (n < 0 ? 1 : 0);
	s[i + 1] = '\0';
	if (n < 0)
		s[0] = '-';
	while (nb >= 10)
	{
		s[i] = nb % 10 + 48;
		nb = nb / 10;
		i--;
	}
	s[i] = nb + 48;
	return (s);
}
