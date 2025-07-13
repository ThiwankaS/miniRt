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

t_compute	prepare_compute(t_intersect *i, t_ray *r)
{
	float		mul;
	t_compute	comp;

	comp.value = i->value;
	comp.object = i->object;
	position(&comp.p, r, i->value);
	tuple_negate(&comp.eye_v, &r->direction);
	normal_at(&comp.normal_v, i->object, &comp.p);
	mul = dot(&comp.eye_v, &comp.normal_v);
	if(mul < 0)
	{
		comp.inside = true;
		tuple_negate(&comp.normal_v, &comp.normal_v);
	}
	else
		comp.inside = false;
	return (comp);
}

void shade_hit(t_tuple *colour, t_object *object, t_world *world, t_compute *comp)
{
	lighting(colour, object->material, &world->light, &comp->p, &comp->eye_v, &comp->normal_v);
}

t_tuple	color_at(t_world *world, t_ray *r)
{
	t_tuple		colour;
	t_intersect	*xs;
	t_intersect	*i;
	t_compute	comp;

	color(&colour, 0.0f, 0.0f, 0.0f);
	xs = intersect_world(world, r);
	xs = intersections_sort(xs);
	i = hit(xs);
	if (i)
	{
		comp = prepare_compute(i, r);
		shade_hit(&colour, i->object, world, &comp);
		free_intersections(xs);
		return (colour);
	}
	free_intersections(xs);
	return (colour);
}

void view_transformation(t_camera *camera, t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple sub;
	t_tuple forward;
	t_tuple left;
	t_tuple true_up;
	t_mat orientation;
	t_mat translate;

	tuple_subtract(&sub, to, from);
	normalize(&forward, &sub);
	cross(&left, &forward, up);
	cross(&true_up, &left, &forward);
	identity(&orientation);
	orientation.m[0][0] = left.t[0];
	orientation.m[0][1] = left.t[1];
	orientation.m[0][2] = left.t[2];
	orientation.m[1][0] = true_up.t[0];
	orientation.m[1][1] = true_up.t[1];
	orientation.m[1][2] = true_up.t[2];
	orientation.m[2][0] = -forward.t[0];
	orientation.m[2][1] = -forward.t[1];
	orientation.m[2][2] = -forward.t[2];
	orientation.m[3][3] = 1;
	translation(&translate, -from->t[0], -from->t[1], -from->t[2]);
	matrix_multiply(&camera->transform, &orientation, &translate);
	matrix_inverse(&camera->invs, &camera->transform);
}

t_camera *camera_init(int hsize, int vsize, float fov)
{
	float	half_view;
	float	aspect;
	t_camera *camera;

	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (NULL);
	camera->hsize = hsize;
	camera->vsize = vsize;
	camera->fov = fov;
	identity(&camera->transform);
	matrix_inverse(&camera->invs, &camera->transform);
	half_view = tan(fov/2);
	aspect = hsize /(float) vsize;
	if(aspect >= 1)
	{
		camera->half_width = half_view;
		camera->half_height = half_view / aspect;
	}
	else
	{
		camera->half_width = half_view * aspect;
		camera->half_height = half_view;
	}
	camera->pixel_size = (camera->half_width * 2) / camera->hsize;
	return (camera);
}

t_ray ray_for_pixel(t_camera *camera, int px, int py)
{
	float	xoffset;
	float	yoffset;
	float	world_x;
	float	world_y;
	t_tuple	p;
	t_tuple	abs_p;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	temp;
	t_tuple	direction;
	t_ray	r;

	xoffset = (px + 0.5) * camera->pixel_size;
	yoffset = (py + 0.5) * camera->pixel_size;
	world_x = camera->half_width - xoffset;
	world_y = camera->half_height - yoffset;
	point(&p, world_x, world_y, -1);
	point(&abs_p, 0.0f, 0.0f, 0.0f);
	matrix_multiply_by_tuple(&pixel, &camera->invs, &p);
	matrix_multiply_by_tuple(&origin, &camera->invs, &abs_p);
	tuple_subtract(&temp, &pixel, &origin);
	normalize(&direction, &temp);
	vector(&r.direction, direction.t[0], direction.t[1], direction.t[2]);
	point(&r.origin, origin.t[0], origin.t[1], origin.t[2]);
	return (r);
}

void render(mlx_image_t *img, t_camera *camera, t_world *world)
{
	int		x;
	int		y;
	t_ray	r;
	t_tuple	colour;

	y = 0;
	while (y < camera->vsize)
	{
		x = 0;
		while (x < camera->hsize)
		{
			r = ray_for_pixel(camera, x, y);
			colour = color_at(world, &r);
			mlx_put_pixel(img, x, y, tuple_to_color(&colour));
			x++;
		}
		y++;
	}
}
