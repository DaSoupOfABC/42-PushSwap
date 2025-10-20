/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_psuh_operations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 03:08:17 by jenlee            #+#    #+#             */
/*   Updated: 2025/06/18 11:52:58 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/push_swap.h"

static void	rotate_stack(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next_node)
		return ;
	first = *stack;
	*stack = first->next_node;
	(*stack)->prev_node = NULL;
	first->next_node = NULL;
	last = *stack;
	while (last->next_node)
		last = last->next_node;
	last->next_node = first;
	first->prev_node = last;
}

void	ra(t_stack **a, int *counter)
{
	rotate_stack(a);
	ft_putstr("ra\n");
	if (counter)
		(*counter)++;
}

void	rb(t_stack **b, int *counter)
{
	rotate_stack(b);
	ft_putstr("rb\n");
	if (counter)
		(*counter)++;
}

void	rr(t_stack **a, t_stack **b, int *counter)
{
	rotate_stack(a);
	rotate_stack(b);
	ft_putstr("rr\n");
	if (counter)
		(*counter)++;
}
