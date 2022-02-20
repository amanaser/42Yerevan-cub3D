/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 16:30:43 by abadalya          #+#    #+#             */
/*   Updated: 2021/02/01 17:35:47 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	unsigned int	i;
	size_t			s_len;

	i = 0;
	if (!s)
		return (NULL);
	s_len = ft_strlen(s + start);
	if (len > s_len)
		len = s_len;
	if (start > ft_strlen(s))
		return (NULL);
	if (!(p = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		*(p + i) = *(s + start + i);
		++i;
	}
	*(p + i) = '\0';
	return (p);
}
