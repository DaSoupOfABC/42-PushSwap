
#include "../../headers/push_swap.h"
#include <limits.h>

/* ---------- Rank helpers (no idx field required) ---------- */

// Count how many values in A∪B are strictly less than `val` → rank 0..n-1
static int rank_of_all(t_stack *a, t_stack *b, int val)
{
    int r = 0;
    for (t_stack *p = a; p; p = p->next_node)
        if (p->num < val) r++;
    for (t_stack *p = b; p; p = p->next_node)
        if (p->num < val) r++;
    return r;
}

// Window size tuned for 500: ~45–55 is a good band. Keep 100 small-ish too.
static int window_for_size(int size)
{
    if (size <= 100) return size / 5;      // ~20
    return 50;                              // empirically solid for 500
}

/* ---------- Tiny stack utilities ---------- */

static void rotate_to_top_a(t_stack **a, int pos, int *counter)
{
    int size = count_stack(*a);
    if (size == 0) return;
    if (pos <= size / 2) while (pos-- > 0) ra(a, counter);
    else                 while (pos++ < size) rra(a, counter);
}

/*static void rotate_to_top_b(t_stack **b, int pos, int *counter)
{
    int size = count_stack(*b);
    if (size == 0) return;
    if (pos <= size / 2) while (pos-- > 0) rb(b, counter);
    else                 while (pos++ < size) rrb(b, counter);
}*/

/* ---------- Insertion target in A (wrap-around aware) ---------- */

static int fits_between(int cur, int next, int val, int minv, int maxv)
{
    // wrap (max -> min)
    if (cur == maxv && next == minv)
        return (val > cur || val < next);
    // normal interval
    return (val > cur && val < next);
}

// Find position in A where `val` should be inserted to keep A ascending.
// Returns index (0..|A|) meaning: rotate A so that this index becomes top, then pa.
static int target_pos_in_a(t_stack *a, int val)
{
    if (!a || !a->next_node) return 0;

    int minv = get_min_value(a);
    int maxv = get_max_value(a);

    int pos = 0;
    t_stack *cur = a;
    while (cur->next_node)
    {
        if (fits_between(cur->num, cur->next_node->num, val, minv, maxv))
            return pos + 1;
        cur = cur->next_node;
        pos++;
    }
    // also check last->first boundary
    if (fits_between(cur->num, a->num, val, minv, maxv))
        return 0;

    // Outside range → before min or after max:
    // If val < min → insert before min (rotate min to top).
    if (val < minv) return find_position(a, minv);
    // If val > max → insert right after max (index after max).
    return (find_position(a, maxv) + 1) % (pos + 1);
}

/* ---------- Costed dual-rotation plan ---------- */

static void apply_best_rotation_plan(t_stack **a, t_stack **b,
                                     int pos_a, int pos_b,
                                     int *counter)
{
    int sa = count_stack(*a);
    int sb = count_stack(*b);

    int ra_cnt  = pos_a;
    int rra_cnt = sa - pos_a;
    int rb_cnt  = pos_b;
    int rrb_cnt = sb - pos_b;

    // Four plans
    int cost_rr     = (ra_cnt > rb_cnt)  ? ra_cnt  : rb_cnt;   // max
    int cost_rrr    = (rra_cnt > rrb_cnt)? rra_cnt : rrb_cnt;  // max
    int cost_ra_rrb = ra_cnt + rrb_cnt;
    int cost_rra_rb = rra_cnt + rb_cnt;

    // Pick cheapest
    int plan = 0; // 0=rr,1=rrr,2=ra+rrb,3=rra+rb
    int best = cost_rr;
    if (cost_rrr < best)  { best = cost_rrr;  plan = 1; }
    if (cost_ra_rrb < best){ best = cost_ra_rrb; plan = 2; }
    if (cost_rra_rb < best){ best = cost_rra_rb; plan = 3; }

    if (plan == 0) {
        // rr phase
        while (ra_cnt > 0 && rb_cnt > 0) { rr(a, b, counter); ra_cnt--; rb_cnt--; }
        while (ra_cnt-- > 0) ra(a, counter);
        while (rb_cnt-- > 0) rb(b, counter);
    }
    else if (plan == 1) {
        // rrr phase
        while (rra_cnt > 0 && rrb_cnt > 0) { rrr(a, b, counter); rra_cnt--; rrb_cnt--; }
        while (rra_cnt-- > 0) rra(a, counter);
        while (rrb_cnt-- > 0) rrb(b, counter);
    }
    else if (plan == 2) {
        while (ra_cnt-- > 0)  ra(a, counter);
        while (rrb_cnt-- > 0) rrb(b, counter);
    }
    else { // plan == 3
        while (rra_cnt-- > 0) rra(a, counter);
        while (rb_cnt-- > 0)  rb(b, counter);
    }
}

/* ---------- Phase 1: windowed push A -> B (rank-based) ---------- */

static void push_windowed(t_stack **a, t_stack **b, int size, int *counter)
{
    int w   = window_for_size(size);
    int lo  = 0;
    int hi  = (w - 1 < size - 1) ? (w - 1) : (size - 1);

    while (*a)
    {
        int top = (*a)->num;
        int idx = rank_of_all(*a, *b, top);

        if (idx < lo) {
            pb(a, b, counter);
            rb(b, counter);          // bury very small ranks
            lo++;
            if (hi < size - 1) hi++;
        }
        else if (idx <= hi) {
            pb(a, b, counter);       // inside window
            lo++;
            if (hi < size - 1) hi++;
        }
        else {
            ra(a, counter);          // not yet in window → advance A
        }
    }
}

/* ---------- Phase 2: greedy return B -> A with costed rotations ---------- */

static void greedy_return(t_stack **a, t_stack **b, int *counter)
{
    while (*b)
    {
        // Choose the current max in B (fast & effective with windowed push)
        int val = get_max_value(*b);
        int pos_b = find_position(*b, val);
        int pos_a = target_pos_in_a(*a, val);

        apply_best_rotation_plan(a, b, pos_a, pos_b, counter);
        pa(a, b, counter);
    }

    // Normalize A (min on top)
    int pos_min = find_position(*a, get_min_value(*a));
    rotate_to_top_a(a, pos_min, counter);
}

/* ---------- Public entry ---------- */

void chunk_sort(t_stack **a, t_stack **b, int size, int *counter)
{
    // Phase 1: push A -> B using a sliding rank window
    push_windowed(a, b, size, counter);

    // Phase 2: greedy/costed reinsertion
    greedy_return(a, b, counter);
}
