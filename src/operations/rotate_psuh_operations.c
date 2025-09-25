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
