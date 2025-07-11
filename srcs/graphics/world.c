#include "../../include/miniRt.h"

t_intersect	*intersect_world(t_world *w, t_ray *r)
{
	t_intersect	*xs;
	t_object	*current;

	xs = NULL;
	current = w->components;
	while (current)
	{
		xs = cal_intersects(current, r, xs);
		current = current->next;
	}
	return (xs);
}
