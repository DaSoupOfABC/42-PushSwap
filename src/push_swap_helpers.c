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

char	*join_all_args(int argc, char **argv)
{
	char	*joined;
	char	*tmp;
	int		i;

	joined = ft_strdup("");
	if (!joined)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		tmp = joined;
		joined = ft_strjoin(joined, argv[i]);
		free(tmp);
		if (i < argc - 1)
		{
			tmp = joined;
			joined = ft_strjoin(joined, " ");
			free(tmp);
		}
		i++;
	}
	return (joined);
}

int	parse_args(int argc, char ***args, int *count)
{
	char	*joined;

	joined = join_all_args(argc, *args);
	if (!joined)
		return (ft_putstr_fd("Error\n", 2), 0);
	*args = ft_split(joined, ' ');
	free(joined);
	if (!*args)
		return (ft_putstr_fd("Error\n", 2), 0);
	*count = 0;
	while ((*args)[*count])
		(*count)++;
	return (1);
}
