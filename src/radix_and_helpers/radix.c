/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:26:28 by jenlee            #+#    #+#             */
/*   Updated: 2025/09/05 16:48:52 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/push_swap.h"
#include "push_swap.h"

// Get how many bits are needed to represent the largest index
static int get_max_bits(int size)
{
    int max;
    int bits;

    max = size - 1; // since indices go from 0..size-1
    bits = 0;
    while ((max >> bits) != 0)
        bits++;
    return (bits);
}

// Return the value at the top of stack A
static int top_value(t_stack *stack)
{
    if (!stack)
        return (0);
    return (stack->num);
}

void radix_sort(t_stack **a, t_stack **b, int size, int *counter)
{
    int i;
    int j;
    int max_bits;
    int num;

    max_bits = get_max_bits(size);
    i = 0;
    while (i < max_bits)
    {
        j = 0;
        while (j < size)
        {
            num = top_value(*a);
            if (((num >> i) & 1) == 0)
                pb(a, b, counter);  // bit = 0 → push to B
            else
                ra(a, counter);     // bit = 1 → rotate A
            j++;
        }
        while (*b != NULL)
            pa(a, b, counter);      // bring everything back
        i++;
    }
}
