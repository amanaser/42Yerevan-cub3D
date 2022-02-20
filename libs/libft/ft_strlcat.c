/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:56:43 by abadalya          #+#    #+#             */
/*   Updated: 2021/01/26 17:57:59 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t n;
	size_t m;

	n = 0;
	m = 0;
	while (dest[n] && n < size)
		n++;
	while (src[m] && (m + n + 1) < size)
	{
		dest[n + m] = src[m];
		m++;
	}
	if (n < size)
		dest[n + m] = '\0';
	return (n + ft_strlen(src));
}
