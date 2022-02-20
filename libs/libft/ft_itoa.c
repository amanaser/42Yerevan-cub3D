/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 15:11:04 by abadalya          #+#    #+#             */
/*   Updated: 2021/01/31 14:58:28 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	len(int a)
{
	int len;

	len = 0;
	if (a <= 0)
		len++;
	while (a)
	{
		a /= 10;
		len++;
	}
	return (len);
}

char		*ft_itoa(int n)
{
	char	*p;
	int		l;
	long	num;

	num = n;
	l = len(num);
	if (!(p = (char *)malloc(sizeof(char) * (l + 1))))
		return (NULL);
	if (num == 0)
		p[0] = '0';
	else if (num < 0)
	{
		p[0] = '-';
		num *= -1;
	}
	p[l--] = '\0';
	while (num)
	{
		p[l] = num % 10 + '0';
		l--;
		num /= 10;
	}
	return (p);
}
