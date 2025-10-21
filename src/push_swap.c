/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 00:13:03 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/20 01:02:04 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/push_swap.h"

int	handle_error(t_mainvars *v, int argc, int print_err)
{
	if (print_err)
		ft_putstr_fd("Error\n", 2);
	if (argc == 2 && v->args)
		free_split(v->args);
	free(v->indexed);
	free(v->num_array);
	return (1);
}

static long long	*parse_numbers(int argc, char *argv[], int *error)
{
	long long	*vals;
	int			i;
	int			err;

	vals = malloc(sizeof(long long) * (argc - 1));
	if (!vals)
		return (NULL);
	i = 1;
	while (i < argc)
	{
		vals[i - 1] = ft_atoi_pushswap(argv[i], &err);
		if (err)
		{
			free(vals);
			*error = 1;
			return (NULL);
		}
		i++;
	}
	*error = 0;
	return (vals);
}

int	check_dup_values(int argc, char *argv[])
{
	long long	*vals;
	int			i;
	int			j;
	int			error;

	vals = parse_numbers(argc, argv, &error);
	if (!vals || error)
		return (-1);
	i = 0;
	while (i < argc - 2)
	{
		j = i + 1;
		while (j < argc - 1)
		{
			if (vals[i] == vals[j])
			{
				free(vals);
				return (-1);
			}
			j++;
		}
		i++;
	}
	free(vals);
	return (0);
}

static int	setup_and_validate(t_mainvars *v, int argc, char **argv)
{
	if (!parse_args(argc, &argv, &v->arg_count))
		return (1);
	v->args = argv;
	if (check_dup_values(v->arg_count + 1, v->args - 1) != 0)
		return (handle_error(v, argc, 1));
	if (!init_and_validate(v->arg_count + 1, v->args - 1,
			&v->num_array, &v->indexed)
		|| !lists(v->indexed, v->arg_count, &v->a))
		return (handle_error(v, argc, 0));
	return (0);
}

int	main(int argc, char **argv)
{
	t_mainvars	v;

	ft_bzero(&v, sizeof(t_mainvars));
	if (argc < 2)
		exit(0);
	if (argc == 2 && is_empty_string(argv[1]))
	{
		ft_putstr_fd("Error\n", 2);
		exit(1);
	}
	if (setup_and_validate(&v, argc, argv))
		return (1);
	if (!is_sorted(v.a))
		main_sort(&v.a, &v.b, v.arg_count);
	ft_lstclear_mod(&v.a, free);
	ft_lstclear_mod(&v.b, free);
	handle_error(&v, argc, 0);
	return (0);
}
