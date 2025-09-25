/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate_operations.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:23:10 by jenlee            #+#    #+#             */
/*   Updated: 2025/06/18 11:52:41 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/push_swap.h"

static void	reverse_rotate_stack(t_stack **stack)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!stack || !*stack || !(*stack)->next_node)
		return ;
	last = *stack;
	while (last->next_node)
		last = last->next_node;
	second_last = last->prev_node;
	second_last->next_node = NULL;
	last->prev_node = NULL;
	last->next_node = *stack;
	(*stack)->prev_node = last;
	*stack = last;
}

void	rra(t_stack **a, int *counter)
{
	reverse_rotate_stack(a);
	ft_putstr("rra\n");
	if (counter)
		(*counter)++;
}

void	rrb(t_stack **b, int *counter)
{
	reverse_rotate_stack(b);
	ft_putstr("rrb\n");
	if (counter)
		(*counter)++;
}

void	rrr(t_stack **a, t_stack **b, int *counter)
{
	reverse_rotate_stack(a);
	reverse_rotate_stack(b);
	ft_putstr("rrr\n");
	if (counter)
		(*counter)++;
}
