/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jenlee <jenlee@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:07:44 by jenlee            #+#    #+#             */
/*   Updated: 2025/09/05 18:26:58 by jenlee           ###   ########.fr       */
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

typedef struct s_move
{
    int pos_b;
    int pos_a;
    int cost_a;
    int cost_b;
    int total_cost;
} 						t_move;

void	sort_array(int *arr, int size);
void	assign_indices(int *original, int *indexed, int size);
t_stack	*ft_lstlast_mod(t_stack *lst);
void	ft_lstadd_back_mod(t_stack **lst, t_stack *new_node);
void	ft_lstadd_front_mod(t_stack **lst, t_stack *new_node);
void	ft_lstdelone_mod(t_stack *lst, void (*del)(void *));
void	ft_lstclear_mod(t_stack **lst, void (*del)(void *));
t_stack	*ft_lstnew_mod(int num);
int		ft_atoi_pushswap(const char *str, int *error);
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
void radix_sort(t_stack **a, t_stack **b, int size, int *counter);
int		get_max_value(t_stack *stack);
void	main_sort(t_stack **a, t_stack **b, int size);
void	rotate_to_chunk(t_stack **a, int limit, int *counter);
int		is_sorted(t_stack *a);

//void	greedy_return(t_stack **a, t_stack **b, int *counter);

void	push_and_return_chunks(t_stack **a, t_stack **b, int size\
, int *counter);
int		count_stack(t_stack *stack);
int		find_position(t_stack *stack, int target);
int		find_next_chunk_index(t_stack *a, int limit);
int		chunk_sized(int size);
int		get_min_value(t_stack *stack);
int		get_value_at(t_stack *stack, int index);


void chunk_sort(t_stack **a, t_stack **b, int size, int *counter);
void greedy_sort(t_stack **a, t_stack **b, int *counter);

#endif
