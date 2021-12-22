/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 10:43:56 by esivre            #+#    #+#             */
/*   Updated: 2021/05/22 16:42:07 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*ret;

	if (!lst)
		return (NULL);
	dest = ft_lstnew((f)(lst->content));
	if (!dest)
		return (NULL);
	ret = dest;
	lst = lst->next;
	while (lst)
	{
		dest->next = ft_lstnew((f)(lst->content));
		if (!dest->next)
		{
			ft_lstclear(&ret, del);
			return (NULL);
		}
		dest = dest->next;
		lst = lst->next;
	}
	dest->next = NULL;
	return (ret);
}
