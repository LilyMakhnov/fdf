/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 12:09:30 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:43:51 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nbr)
{
	unsigned long	res;
	int				sign;

	res = 0;
	sign = 1;
	while (*nbr == ' ' || (*nbr >= 9 && *nbr <= 13))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
		if (*nbr++ == '-')
			sign *= -1;
	while (ft_isdigit(*nbr))
	{
		if (res >= 922337203685477580 && sign == 1)
			return (-1);
		if (res >= 922337203685477580 && sign == -1)
			return (0);
		res = res * 10 + *nbr++ - '0';
	}
	return (sign * res);
}
