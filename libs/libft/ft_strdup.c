/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:44:32 by abadalya          #+#    #+#             */
/*   Updated: 2021/01/26 18:47:03 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		len;

	len = 0;
	s2 = (char *)malloc(ft_strlen(s1) + 1);
	if (s2 == 0)
		return (s2);
	while (*(s1 + len) != '\0')
	{
		*(s2 + len) = *(s1 + len);
		len++;
	}
	*(s2 + len) = '\0';
	return (s2);
}
