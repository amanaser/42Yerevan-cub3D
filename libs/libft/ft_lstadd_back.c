/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 18:43:55 by abadalya          #+#    #+#             */
/*   Updated: 2021/02/01 14:37:54 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list *mylst;

	if (*lst)
	{
		mylst = ft_lstlast(*lst);
		mylst->next = new;
		new->next = NULL;
	}
	else
	{
		*lst = new;
		new->next = NULL;
	}
}
