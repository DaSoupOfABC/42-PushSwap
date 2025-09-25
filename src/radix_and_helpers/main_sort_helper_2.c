#include <limits.h>
#include "../../headers/push_swap.h"
int get_stack_index(t_stack *stack, int value);

typedef struct s_cost_info
{
    int b_val;
    int a_rot;
    int b_rot;
    int total_cost;
} t_cost_info;


int get_max_value(t_stack *stack)
{
    int max = stack->num;
    while (stack)
    {
        if (stack->num > max)
            max = stack->num;
        stack = stack->next_node;
    }
    return (max);
}

int get_min_value(t_stack *stack)
{
    if (!stack)
    {
        write(2, "Error: get_min_value called with NULL stack\n", 45);
        return 0;
    }
    int min = stack->num;
    while (stack)
    {
        if (stack->num < min)
            min = stack->num;
        stack = stack->next_node;
    }
    return (min);
}

int get_value_at(t_stack *stack, int index)
{
    int i = 0;
    while (stack && i < index)
    {
        stack = stack->next_node;
        i++;
    }
    return (stack ? stack->num : 0);
}

void rotate_to_chunk(t_stack **a, int limit, int *counter)
{
    int best_index = -1;
    int best_cost = INT_MAX;
    t_stack *tmp = *a;
    int len = count_stack(*a);

    // Step 1: Find the best candidate under the limit
    for (int i = 0; tmp; tmp = tmp->next_node, i++)
    {
        if (tmp->num < limit)
        {
            int cost = (i <= len / 2) ? i : len - i;
            if (cost < best_cost)
            {
                best_cost = cost;
                best_index = i;
            }
        }
    }

    // Step 2: Rotate to that node
    if (best_index == -1)
        return; // nothing to rotate

    if (best_index <= len / 2)
    {
        while (best_index-- > 0)
            ra(a, counter);
    }
    else
    {
        best_index = len - best_index;
        while (best_index-- > 0)
            rra(a, counter);
    }
}

int is_sorted(t_stack *a)
{
    while (a && a->next_node)
    {
        if (a->num > a->next_node->num)
            return (0);
        a = a->next_node;
    }
    return (1);
}

int ft_max(int a, int b)
{
    return (a > b ? a : b);
}

int total_cost(int a_rot, int b_rot)
{
    if ((a_rot >= 0 && b_rot >= 0) || (a_rot < 0 && b_rot < 0))
        return (ft_max(abs(a_rot), abs(b_rot))); // Shared `rr`/`rrr`
    else
        return (abs(a_rot) + abs(b_rot)); // Different direction, can't pair
}

int rotation_cost(int len, int index)
{
    if (index <= len / 2)
        return index;  // Rotate forward
    else
        return -(len - index);  // Rotate backward
}


int find_best_insert_index(t_stack *a, int b_val)
{
    int index = 0;
    t_stack *curr = a;

    while (curr)
    {
        int curr_num = curr->num;
        int next_num = curr->next_node ? curr->next_node->num : a->num;

        if ((b_val > curr_num && b_val < next_num) ||
            (curr_num > next_num && (b_val < next_num || b_val > curr_num)))
        {
            return index + 1;
        }

        curr = curr->next_node;
        index++;
    }

    return (0);
}

int find_rotation_count(t_stack *stack, int target)
{
    int i = 0;
    t_stack *tmp = stack;
    while (tmp && tmp->num != target)
    {
        tmp = tmp->next_node;
        i++;
    }
    int len = count_stack(stack);
    return (i <= len / 2) ? i : i - len; // Positive = ra, Negative = rra
}

int find_insert_position_value(t_stack *a, int b_val)
{
    t_stack *tmp = a;
    t_stack *best = NULL;
    int min_val;

    // Find smallest number larger than b_val
    while (tmp)
    {
        if (tmp->num > b_val && (!best || tmp->num < best->num))
            best = tmp;
        tmp = tmp->next_node;
    }

    if (!best)
    {
        min_val = get_min_value(a);
        return min_val;
    }
    return best->num;
}

int get_stack_index(t_stack *stack, int value)
{
    int i = 0;
    while (stack)
    {
        if (stack->num == value)
            return i;
        stack = stack->next_node;
        i++;
    }
    return -1;
}

void greedy_return(t_stack **a, t_stack **b, int *counter)
{
    while (*b)
    {
        int best_cost = INT_MAX;
        int best_a_rot = 0, best_b_rot = 0;
        int best_b_val = (*b)->num;
        int len_b = count_stack(*b);
      //  int len_a = count_stack(*a);

        t_stack *curr_b = *b;
        for (int i = 0; curr_b; curr_b = curr_b->next_node, i++)
        {
            int b_val = curr_b->num;
            int b_rot = rotation_cost(len_b, i);
            int insert_index = find_best_insert_index(*a, b_val);
            int a_rot = rotation_cost(count_stack(*a), insert_index);
            int cost = total_cost(a_rot, b_rot);

            if (cost < best_cost || (cost == best_cost && abs(b_rot) < abs(best_b_rot)))
            {
                best_cost = cost;
                best_b_val = b_val;
                best_a_rot = a_rot;
                best_b_rot = b_rot;
            }
        }

        // Perform shared rotations
        while (best_a_rot > 0 && best_b_rot > 0)
        {
            rr(a, b, counter);
            best_a_rot--;
            best_b_rot--;
        }
        while (best_a_rot < 0 && best_b_rot < 0)
        {
            rrr(a, b, counter);
            best_a_rot++;
            best_b_rot++;
        }

        // Individual rotations
        while (best_a_rot > 0) { ra(a, counter); best_a_rot--; }
        while (best_a_rot < 0) { rra(a, counter); best_a_rot++; }

        while ((*b)->num != best_b_val)
        {
            if (best_b_rot > 0) { rb(b, counter); best_b_rot--; }
            else { rrb(b, counter); best_b_rot++; }
        }

        pa(a, b, counter);
    }

    // Final rotate A so min value is on top
    int min = get_min_value(*a);
    int pos = get_stack_index(*a, min);
    int rot = rotation_cost(count_stack(*a), pos);
    while (rot > 0) { ra(a, counter); rot--; }
    while (rot < 0) { rra(a, counter); rot++; }
}


void push_and_return_chunks(t_stack **a, t_stack **b, int size, int *counter)
{
    int chunk_size;
    int limit;
    int pushed;

    // Adaptive chunk sizing for larger sets of data
    if (size <= 100)
        chunk_size = size / 4;
    else if (size <= 300)
        chunk_size = size / 8;  // Smaller chunks for medium sizes
    else
        chunk_size = size / 12;  // Even smaller chunks for larger sizes

    limit = chunk_size;
    pushed = 0;

    // Iterate until all elements are pushed
    while (pushed < size)
    {
        if (is_sorted(*a) && (*b) == NULL)
            return;

        int pos = find_next_chunk_index(*a, limit);

        int attempt = 0;
        if (pos == -1 && attempt++ < 3)
        {
            limit += chunk_size;
            continue;
        }
        else if (pos == -1)
        {
            break; // Break if no valid chunk is found after multiple attempts
        }

        rotate_to_chunk(a, limit, counter);

        // After rotate, top of A should be part of chunk
        if ((*a)->num < limit)
        {
            int pushed_val = (*a)->num;
            pb(a, b, counter);
            pushed++;

            // Move elements in B to correct position if needed
            if (size > 100 && pushed_val < (limit - chunk_size / 2))
                rb(b, counter);
        }
    }

    greedy_return(a, b, counter);
}