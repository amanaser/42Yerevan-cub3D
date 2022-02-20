/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:10:16 by abadalya          #+#    #+#             */
/*   Updated: 2021/02/01 16:05:23 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		set_check(char const *set, char const c)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*p;
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	if (!s1)
		return (NULL);
	while (set_check(set, *s1))
		s1++;
	if (!*s1)
	{
		p = ft_strdup("");
		return (p);
	}
	len = ft_strlen(s1);
	while (set_check(set, *(s1 + len - 1)))
		len--;
	if (!(p = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	ft_memcpy(p, s1, len);
	*(p + len) = '\0';
	return (p);
}
