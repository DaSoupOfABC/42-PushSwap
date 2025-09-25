#include "../../headers/push_swap.h"

/* ===========================================================
   Insert position logic
   =========================================================== */

static int fits_between(int cur, int next, int val, int min, int max)
{
    // Handle wrap-around between max → min
    if (cur == max && next == min)
        return (val > cur || val < next);
    return (val > cur && val <= next);
}

static int find_insert_position(t_stack *a, int val)
{
    int     min;
    int     max;
    int     pos;
    t_stack *cur;

    min = get_min_value(a);
    max = get_max_value(a);
    pos = 0;
    cur = a;
    while (cur->next_node)
    {
        if (fits_between(cur->num, cur->next_node->num, val, min, max))
            return (pos + 1);
        cur = cur->next_node;
        pos++;
    }
    // If val < min → before min
    if (val < min)
        return find_position(a, min);
    // If val > max → after max
    if (val > max)
        return find_position(a, max) + 1;
    return (0);
}

/* ===========================================================
   Greedy sort main
   =========================================================== */

void    greedy_sort(t_stack **a, t_stack **b, int *counter)
{
    int min;
    int max;

    if (!a || !*a || count_stack(*a) < 2)
        return;
    min = get_min_value(*a);
    max = get_max_value(*a);

    /* Step 1: Push everything except min & max into B */
    while (count_stack(*a) > 2)
    {
        if ((*a)->num == min || (*a)->num == max)
            ra(a, counter);
        else
            pb(a, b, counter);
    }

    /* Step 2: Greedy re-insert from B */
    while (*b)
    {
        int val = (*b)->num;
        int pos = find_insert_position(*a, val);
        int size = count_stack(*a);

        // rotate A to correct position
        if (pos <= size / 2)
            while (pos-- > 0)
                ra(a, counter);
        else
        {
            pos = size - pos;
            while (pos-- > 0)
                rra(a, counter);
        }
        pa(a, b, counter);
    }

    /* Step 3: Rotate A so that min is at the top */
    int pos_min = find_position(*a, get_min_value(*a));
    int size = count_stack(*a);
    if (pos_min <= size / 2)
        while (pos_min-- > 0)
            ra(a, counter);
    else
    {
        pos_min = size - pos_min;
        while (pos_min-- > 0)
            rra(a, counter);
    }
}
