/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:15:45 by abadalya          #+#    #+#             */
/*   Updated: 2021/02/01 15:28:49 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char buff[len];

	if (!dst && !src)
		return (NULL);
	ft_memcpy(buff, src, len);
	ft_memcpy(dst, buff, len);
	return (dst);
}
