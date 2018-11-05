/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:28:03 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/29 17:28:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	void	*content_copy;
	t_list	*lst;

	lst = (t_list *)malloc(sizeof(t_list));
	if (lst)
	{
		if (!content)
		{
			lst->content = NULL;
			lst->content_size = 0;
		}
		else
		{
			content_copy = malloc(content_size);
			if (content_copy)
				lst->content = ft_memcpy(content_copy, content, content_size);
			lst->content_size = content_size;
		}
		lst->next = NULL;
	}
	return (lst);
}
