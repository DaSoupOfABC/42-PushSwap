/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:05:46 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/20 00:14:16 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	check_dup(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = i + 1;
		while (j < argc)
		{
			if (ft_strcmp(argv[i], argv[j]) == 0)
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	lists(int *num, int size, t_stack **a)
{
	int		i;
	t_stack	*new_node;

	i = 0;
	while (i < size)
	{
		new_node = ft_lstnew_mod(num[i]);
		if (!new_node)
		{
			ft_lstclear_mod(a, free);
			return (0);
		}
		ft_lstadd_back_mod(a, new_node);
		i++;
	}
	return (1);
}

int	init_and_validate(int argc, char **argv, int **nums, int **indexed)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	*nums = malloc(sizeof(int) * (argc - 1));
	if (!*nums)
		return (0);
	while (argv[i])
	{
		(*nums)[j] = ft_atoi(argv[i]);
		i++;
		j++;
	}
	*indexed = malloc(sizeof(int) * (argc - 1));
	if (!*indexed)
	{
		free(*nums);
		return (0);
	}
	assign_indices(*nums, *indexed, argc - 1);
	return (1);
}

int	parse_args(int argc, char ***args, int *count)
{
	if (argc == 2)
	{
		*args = ft_split((*args)[1], ' ');
		if (!*args)
			return (ft_putstr_fd("Error\n", 2), 0);
		*count = 0;
		while ((*args)[*count])
			(*count)++;
	}
	else
	{
		*args = *args + 1;
		*count = argc - 1;
	}
	return (1);
}
