/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:07:44 by jenlee            #+#    #+#             */
/*   Updated: 2025/10/20 01:00:06 by jenlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_stack
{
	int				num;
	struct s_stack	*prev_node;
	struct s_stack	*next_node;
}						t_stack;

typedef struct s_mainvars
{
	int		*num_array;
	int		*indexed;
	t_stack	*a;
	t_stack	*b;
	char	**args;
	int		arg_count;
}	t_mainvars;

//Helpers
void	sort_array(int *arr, int size);
void	assign_indices(int *original, int *indexed, int size);
t_stack	*ft_lstlast_mod(t_stack *lst);
void	ft_lstadd_back_mod(t_stack **lst, t_stack *new_node);
void	ft_lstadd_front_mod(t_stack **lst, t_stack *new_node);
void	ft_lstdelone_mod(t_stack *lst, void (*del)(void *));
void	ft_lstclear_mod(t_stack **lst, void (*del)(void *));
t_stack	*ft_lstnew_mod(int num);
int		ft_atoi_pushswap(const char *str, int *error);
int		ft_lstsize_mod(t_stack *lst);
//Setups
int		parse_args(int argc, char ***args, int *count);
int		check_dup(int argc, char *argv[]);
int		check_atoi(int argc, char *argv[]);
int		handle_error(t_mainvars *v, int argc, int print_err);
int		init_and_validate(int argc, char **argv, int **nums, int **indexed);
int		lists(int *num, int size, t_stack **a);
int		is_empty_string(const char *str);
//Operations
void	ra(t_stack **a, int *counter);
void	rb(t_stack **b, int *counter);
void	rr(t_stack **a, t_stack **b, int *counter);
void	pa(t_stack **a, t_stack **b, int *counter);
void	pb(t_stack **a, t_stack **b, int *counter);
void	rra(t_stack **a, int *counter);
void	rrb(t_stack **b, int *counter);
void	rrr(t_stack **a, t_stack **b, int *counter);
void	sa(t_stack **a, int *counter);
void	sb(t_stack **b, int *counter);
void	ss(t_stack **a, t_stack **b, int *counter);
//Sorters
int		top_value(t_stack *stack);
int		get_max_bits(int size, int mode);
void	radix_pushback(t_stack **a, t_stack **b, int *counter);
void	radix_handle_bit(t_stack **a, t_stack **b, int *counter, int bit);
void	radix_sort(t_stack **a, t_stack **b, int size, int *counter);
void	main_sort(t_stack **a, t_stack **b, int size);
int		is_sorted(t_stack *stack);
void	small_sort(t_stack **a, t_stack **b, int *counter, int size);
void	tiny_sort(t_stack **a, t_stack **b, int *counter, int size);
void	align_head(t_stack **a, int *counter);
void	sort_five(t_stack **a, t_stack **b, int *counter);
void	sort_three(t_stack **a, int *counter);
int		find_min_pos(t_stack *stack, int *pos);
void	sort_four(t_stack **a, t_stack **b, int *counter);

#endif