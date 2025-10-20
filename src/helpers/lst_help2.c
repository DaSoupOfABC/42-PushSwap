/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_help2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:26:09 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/18 18:32:14 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

void	ft_lstdelone_mod(t_stack *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	if (del)
		del(&(lst -> num));
}

void	ft_lstclear_mod(t_stack **lst, void (*del)(void *))
{
	t_stack	*temp;

	if (!del || !lst || !*lst)
		return ;
	while (lst && *lst)
	{
		temp = (*lst)-> next_node;
		ft_lstdelone_mod(*lst, del);
		*lst = temp;
	}
}

int	ft_lstsize_mod(t_stack *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next_node;
		i++;
	}
	return (i);
}
