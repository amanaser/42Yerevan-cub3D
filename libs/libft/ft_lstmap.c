/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abadalya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:00:52 by abadalya          #+#    #+#             */
/*   Updated: 2021/02/01 16:16:11 by abadalya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *head;
	t_list *temp;

	if (!lst)
		return (NULL);
	if (!(temp = ft_lstnew(f(lst->content))))
		ft_lstdelone(lst, del);
	else
	{
		head = temp;
		lst = lst->next;
	}
	while (lst)
	{
		if (!(temp->next = ft_lstnew(f(lst->content))))
			ft_lstdelone(lst, del);
		temp = temp->next;
		lst = lst->next;
	}
	return (head);
}
