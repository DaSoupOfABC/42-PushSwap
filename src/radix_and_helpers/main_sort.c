/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 15:00:57 by jenlee            #+#    #+#             */
/*   Updated: 2025/09/05 18:25:28 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/push_swap.h"
int	count_stack(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next_node;
	}
	return (count);
}

int	find_position(t_stack *stack, int target)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->num == target)
			return (pos);
		pos++;
		stack = stack->next_node;
	}
	return (-1);
}

int	find_next_chunk_index(t_stack *a, int limit)
{
	int	i;

	i = 0;
	while (a)
	{
		if (a->num < limit)
			return (i);
		i++;
		a = a->next_node;
	}
	return (-1);
}

int	chunk_sized(int size)
{
	if (size <= 100)
		return (size / 4); //size / 4
	else
		return (size / 11);  //size / 11
}

void	main_sort(t_stack **a, t_stack **b, int size)
{
	int	counter;

	counter = 0;
	if (size == 2 && is_sorted(*a) == 0)
		sa(a, &counter);
	else if (size <30)
		radix_sort(a, b, size, &counter);
	else if (size <=100)
		chunk_sort(a, b, size, &counter);
	else
		//greedy_sort(a,b, &counter);
        chunk_sort(a, b, size, &counter);
		//push_and_return_chunks(a, b, size, &counter);
	ft_putnbr_fd(counter, 1);
}
