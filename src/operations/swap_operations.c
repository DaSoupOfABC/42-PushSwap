/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:33:59 by jenlee            #+#    #+#             */
/*   Updated: 2025/06/18 11:53:45 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/push_swap.h"

static void	swap_stack(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!stack || !*stack || !(*stack)->next_node)
		return ;
	first = *stack;
	second = first->next_node;
	first->next_node = second->next_node;
	if (second->next_node)
		second->next_node->prev_node = first;
	second->prev_node = NULL;
	second->next_node = first;
	first->prev_node = second;
	*stack = second;
}

void	sa(t_stack **a, int *counter)
{
	swap_stack(a);
	ft_putstr("sa\n");
	if (counter)
		(*counter)++;
}

void	sb(t_stack **b, int *counter)
{
	swap_stack(b);
	ft_putstr("sb\n");
	if (counter)
		(*counter)++;
}

void	ss(t_stack **a, t_stack **b, int *counter)
{
	swap_stack(a);
	swap_stack(b);
	ft_putstr("ss\n");
	if (counter)
		(*counter)++;
}
