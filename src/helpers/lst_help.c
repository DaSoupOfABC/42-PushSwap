/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 18:18:33 by jenlee            #+#    #+#             */
/*   Updated: 2025/06/18 11:50:14 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/push_swap.h"

t_stack	*ft_lstlast_mod(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next_node)
		lst = lst -> next_node;
	return (lst);
}

void	ft_lstadd_back_mod(t_stack **lst, t_stack *new_node)
{
	t_stack	*last;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	last = ft_lstlast_mod(*lst);
	last -> next_node = new_node;
	new_node -> prev_node = last;
	new_node -> next_node = NULL;
}

void	ft_lstadd_front_mod(t_stack **lst, t_stack *new_node)
{
	if (!lst || !new_node)
		return ;
	new_node -> next_node = *lst;
	new_node -> prev_node = NULL;
	if (*lst)
		(*lst)-> prev_node = new_node;
	*lst = new_node;
}

t_stack	*ft_lstnew_mod(int num)
{
	t_stack	*new;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (NULL);
	new -> num = num;
	new -> next_node = NULL;
	new -> prev_node = NULL;
	return (new);
}

t_stack	*ft_lstmap_mod(t_stack *lst, int (*f)(int), void (*del)(void *))
{
	t_stack	*new;
	t_stack	*temp;

	if (!f || !lst || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		temp = ft_lstnew_mod(f(lst -> num));
		if (!temp)
		{
			ft_lstclear_mod(&new, del);
			return (NULL);
		}
		ft_lstadd_back_mod(&new, temp);
		lst = lst -> next_node;
	}
	return (new);
}
