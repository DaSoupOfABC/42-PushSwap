/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sorts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 22:10:00 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/18 18:40:29 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/push_swap.h"

int	find_min_pos(t_stack *stack, int *pos)
{
	t_stack	*cur;
	int		min;
	int		i;

	cur = stack;
	min = cur->num;
	i = 0;
	*pos = 0;
	while (cur)
	{
		if (cur->num < min)
		{
			min = cur->num;
			*pos = i;
		}
		cur = cur->next_node;
		i++;
	}
	return (min);
}

void	sort_three(t_stack **a, int *counter)
{
	int	x;
	int	y;
	int	z;

	x = (*a)->num;
	y = (*a)->next_node->num;
	z = (*a)->next_node->next_node->num;
	if (x > y && y < z && x < z)
		sa(a, counter);
	else if (x > y && y > z)
	{
		sa(a, counter);
		rra(a, counter);
	}
	else if (x > y && y < z && x > z)
		ra(a, counter);
	else if (x < y && y > z && x < z)
	{
		sa(a, counter);
		ra(a, counter);
	}
	else if (x < y && y > z && x > z)
		rra(a, counter);
}

void	tiny_sort(t_stack **a, t_stack **b, int *counter, int size)
{
	int	pos;

	while (!is_sorted(*a))
	{
		find_min_pos(*a, &pos);
		if (pos <= size / 2)
			while (pos-- > 0)
				ra(a, counter);
		else
		{
			pos = size - pos;
			while (pos-- > 0)
				rra(a, counter);
		}
		pb(a, b, counter);
		size--;
		if (ft_lstsize_mod(*a) == 2 && !is_sorted(*a))
			sa(a, counter);
	}
	while (*b)
		pa(a, b, counter);
}

void	align_head(t_stack **a, int *counter)
{
	int	pos;
	int	size;

	size = ft_lstsize_mod(*a);
	find_min_pos(*a, &pos);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(a, counter);
	}
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			rra(a, counter);
	}
}

void	sort_four(t_stack **a, t_stack **b, int *counter)
{
	int	pos;
	int	size;

	size = ft_lstsize_mod(*a);
	find_min_pos(*a, &pos);
	if (pos <= size / 2)
		while (pos-- > 0)
			ra(a, counter);
	else
	{
		pos = size - pos;
		while (pos-- > 0)
			rra(a, counter);
	}
	pb(a, b, counter);
	sort_three(a, counter);
	pa(a, b, counter);
}
