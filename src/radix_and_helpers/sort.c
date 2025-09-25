/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 15:53:03 by jenlee            #+#    #+#             */
/*   Updated: 2025/06/16 17:25:03 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../headers/push_swap.h"

static void	merge(int *arr, int left, int mid, int right)
{
	int	i;
	int	j;
	int	k;
	int	*temp;
	int	x;

	i = left;
	j = mid + 1;
	k = 0;
	x = -1;
	temp = ft_calloc((right - left + 1), sizeof(int));
	while (i <= mid && j <= right)
	{
		if (arr[i] < arr[j])
			temp[k++] = arr[i++];
		else
			temp[k++] = arr[j++];
	}
	while (i <= mid)
		temp[k++] = arr[i++];
	while (j <= right)
		temp[k++] = arr[j++];
	while (++x < k)
		arr[left + x] = temp[x];
	free (temp);
}

static void	merge_sort(int *arr, int left, int right)
{
	int	mid;

	if (left < right)
	{
		mid = (left + right) / 2;
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

void	sort_array(int *arr, int size)
{
	if (!arr || size < 2)
		return ;
	merge_sort(arr, 0, size - 1);
}
