/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:05:46 by jenlee            #+#    #+#             */
/*   Updated: 2025/08/21 00:21:31 by jenlee           ###   ########.fr       */
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

int	check_atoi(int argc, char *argv[])
{
	int	i;
	int	error;

	i = 1;
	while (i < argc)
	{
		if (ft_atoi_pushswap(argv[i], &error) == 0 && error)
			return (-1);
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

static int	init_and_validate(int argc, char **argv, int **nums, int **indexed)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	*nums = NULL;
	*indexed = NULL;
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

int	main(int argc, char **argv)
{
	int		*num_array;
	int		*indexed;
	t_stack	*a;
	t_stack	*b;

	a = NULL;
	b = NULL;
	if (argc < 2)
		return (ft_putstr("Too Little Arguments\n"), 1);
	if (check_dup(argc, argv) != 0 || check_atoi(argc, argv) != 0)
		return (ft_putstr_fd("Error\n", 2), 1);
	if (!init_and_validate(argc, argv, &num_array, &indexed))
		return (1);
	if (!lists(indexed, argc - 1, &a))
	{
		free(num_array);
		free(indexed);
		return (1);
	}
	main_sort(&a, &b, argc - 1);
	ft_lstclear_mod(&a, free);
	ft_lstclear_mod(&b, free);
	free(indexed);
	free(num_array);
	return (0);
}
