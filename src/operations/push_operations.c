/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 00:37:37 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/17 00:37:41 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/push_swap.h"

void	pa(t_stack **a, t_stack **b, int *counter)
{
	t_stack	*temp;

	if (!b || !*b)
		return ;
	temp = *b;
	*b = temp->next_node;
	if (*b)
		(*b)->prev_node = NULL;
	temp->next_node = *a;
	if (*a)
		(*a)->prev_node = temp;
	temp->prev_node = NULL;
	*a = temp;
	ft_putstr("pa\n");
	if (counter)
		(*counter)++;
}

void	pb(t_stack **a, t_stack **b, int *counter)
{
	t_stack	*temp;

	if (!a || !*a)
		return ;
	temp = *a;
	*a = temp->next_node;
	if (*a)
		(*a)->prev_node = NULL;
	temp->next_node = *b;
	if (*b)
		(*b)->prev_node = temp;
	temp->prev_node = NULL;
	*b = temp;
	ft_putstr("pb\n");
	if (counter)
		(*counter)++;
}
