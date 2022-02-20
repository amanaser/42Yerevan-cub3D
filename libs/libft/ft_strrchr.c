/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 18:02:33 by abadalya          #+#    #+#             */
/*   Updated: 2021/01/31 14:40:04 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	int		len;

	len = ft_strlen(s);
	str = (char *)s + len;
	while ((len--) + 1)
	{
		if (*str == (char)c)
			return (str);
		str--;
	}
	return (0);
}
