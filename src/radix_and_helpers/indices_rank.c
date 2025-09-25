/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indices_rank.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:47:16 by jenlee            #+#    #+#             */
/*   Updated: 2025/06/16 17:24:52 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/push_swap.h"

int	find_index(int *sorted, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (sorted[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

void	assign_indices(int *original, int *indexed, int size)
{
	int	*sorted;
	int	i;

	i = -1;
	sorted = malloc(sizeof(int) * size);
	if (!sorted)
		return ;
	while (++i < size)
		sorted[i] = original[i];
	sort_array(sorted, size);
	i = -1;
	while (++i < size)
		indexed[i] = find_index(sorted, size, original[i]);
	free(sorted);
}
