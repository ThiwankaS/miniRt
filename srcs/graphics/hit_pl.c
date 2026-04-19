#include "../../include/miniRt.h"

void	find_hit_plane(t_object *object, t_ray *r, t_hit *h)
{
	float	t;

	if (fabsf(r->direction.t[1]) >= EPSILON)
	{
		t = -r->origin.t[1] / r->direction.t[1];
		if (t > EPSILON && t < h->t)
		{
			h->t = t;
			h->object = object;
			h->hit = true;
		}
	}
}
