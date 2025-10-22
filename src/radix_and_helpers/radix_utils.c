/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:20:00 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/17 19:20:00 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/push_swap.h"
#include <math.h>

int	top_value(t_stack *stack)
{
	if (!stack)
		return (-1);
	return (stack->num);
}

int	get_max_bits(int size, int mode)
{
	int	max;
	int	bits;

	max = size - 1;
	bits = 0;
	while ((max >> bits) != 0)
		bits++;
	if (mode == 0)
		return (bits);
	return (0);
}

void	radix_pushback(t_stack **a, t_stack **b, int *counter)
{
	while (*b)
		pa(a, b, counter);
}

void	radix_handle_bit(t_stack **a, t_stack **b, int *counter, int bit)
{
	int	num;

	num = top_value(*a);
	if (((num >> bit) & 1) == 0)
		pb(a, b, counter);
	else
		ra(a, counter);
}
