/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:58:00 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/18 19:06:53 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_stack	*cur;

	cur = stack;
	if (cur == NULL)
		return (1);
	while (cur->next_node != NULL)
	{
		if (cur->num > cur->next_node->num)
			return (0);
		cur = cur->next_node;
	}
	return (1);
}

int	is_misaligned(t_stack *a)
{
	t_stack	*cur;
	int		breaks;
	int		diff;

	breaks = 0;
	cur = a;
	while (cur && cur->next_node)
	{
		diff = cur->next_node->num - cur->num;
		if (diff != 1)
			breaks++;
		cur = cur->next_node;
	}
	if (breaks != 1)
		return (0);
	return (1);
}

void	sort_five(t_stack **a, t_stack **b, int *counter)
{
	int	pos;
	int	size;

	size = ft_lstsize_mod(*a);
	while (size > 3)
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
	}
	sort_three(a, counter);
	if (*b && (*b)->next_node && (*b)->num < (*b)->next_node->num)
		sb(b, counter);
	pa(a, b, counter);
	pa(a, b, counter);
}

void	main_sort(t_stack **a, t_stack **b, int size)
{
	int	counter;

	counter = 0;
	if (is_sorted(*a))
		return ;
	else if (is_misaligned(*a))
	{
		align_head(a, &counter);
		return ;
	}
	else if (size == 2)
		sa(a, &counter);
	else if (size == 3)
		sort_three(a, &counter);
	else if (size == 4)
		sort_four(a, b, &counter);
	else if (size <= 5)
		sort_five(a, b, &counter);
	else if (size <= 10)
		tiny_sort(a, b, &counter, size);
	else
		radix_sort(a, b, size, &counter);
}

//To print operation count, add ft_putnb_fd(counter, 1);
