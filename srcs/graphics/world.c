/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 08:50:58 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 08:52:09 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	is_shadow(t_world *world, t_tuple *p)
{
	float	distance;
	t_tuple	direction;
	t_tuple	v;
	t_ray	shadow_ray;
	t_hit	h;

	distance = 0.0f;
	v = tuple_subtract(&world->light.position, p);
	distance = tuple_magnitute(&v);
	if (distance != 0)
		direction = tuple_divide_scalar(&v, distance);
	else
		vector(&direction, 0.0f, 0.0f, 0.0f);
	shadow_ray.direction = direction;
	shadow_ray.origin = *p;
	h = find_hit(world, &shadow_ray);
	if (h.hit)
	{
		if (h.t < distance)
			return (true);
		return (false);
	}
	return (false);
}

t_compute	prepare_compute(float t, t_object *object, t_ray *r, t_world *world)
{
	t_compute	comp;
	t_tuple		offset;
	float		dot_val;

	comp.value = t;
	comp.object = object;
	position(&comp.p, r, t);
	comp.eye_v = tuple_negate(&r->direction);
	comp.normal_v = normal_at(object, &comp.p);
	dot_val = dot(&comp.eye_v, &comp.normal_v);
	if (dot_val < 0.0f)
	{
		comp.inside = true;
		comp.normal_v = tuple_negate(&comp.normal_v);
	}
	else
	{
		comp.inside = false;
	}
	offset = tuple_multiply_scalar(&comp.normal_v, EPSILON);
	comp.over_p = tuple_add(&comp.p, &offset);
	comp.shadowed = is_shadow(world, &comp.over_p);
	return (comp);
}

t_tuple	color_at(t_world *world, t_ray *r)
{
	t_tuple		colour;
	t_compute	comp;
	t_hit		h;

	h = find_hit(world, r);
	color(&colour, 0.3f, 0.3f, 0.3f);
	if (h.hit)
	{
		comp = prepare_compute(h.t, h.object, r, world);
		colour = lighting(h.object, &world->light, &comp);
		return (colour);
	}
	return (colour);
}

void	view_trans(t_camera *camera, t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple	vec[4];
	t_mat	orientation;
	t_mat	translate;

	vec[0] = tuple_subtract(to, from);
	vec[1] = normalize(&vec[0]);
	vec[2] = cross(&vec[1], up);
	vec[2] = normalize(&vec[2]);
	vec[3] = cross(&vec[2], &vec[1]);
	vec[3] = normalize(&vec[3]);
	orientation = identity();
	orientation.m[0][0] = vec[2].t[0];
	orientation.m[0][1] = vec[2].t[1];
	orientation.m[0][2] = vec[2].t[2];
	orientation.m[1][0] = vec[3].t[0];
	orientation.m[1][1] = vec[3].t[1];
	orientation.m[1][2] = vec[3].t[2];
	orientation.m[2][0] = -vec[1].t[0];
	orientation.m[2][1] = -vec[1].t[1];
	orientation.m[2][2] = -vec[1].t[2];
	orientation.m[3][3] = 1;
	translate = translation(-from->t[0], -from->t[1], -from->t[2]);
	camera->transform = matrix_multiply(&orientation, &translate);
	matrix_inverse(&camera->invs, &camera->transform);
}

t_ray	ray_for_pixel(t_camera *camera, int px, int py)
{
	float	values[4];
	t_tuple	vec[6];
	t_ray	r;

	values[0] = (px + 0.5f) * camera->pixel_size;
	values[1] = (py + 0.5f) * camera->pixel_size;
	values[2] = camera->half_width - values[0];
	values[3] = camera->half_height - values[1];
	point(&vec[0], values[2], values[3], -1.0f);
	point(&vec[1], 0.0f, 0.0f, 0.0f);
	vec[2] = matrix_multiply_by_tuple(&camera->invs, &vec[0]);
	vec[3] = matrix_multiply_by_tuple(&camera->invs, &vec[1]);
	vec[4] = tuple_subtract(&vec[2], &vec[3]);
	vec[5] = normalize(&vec[4]);
	point(&r.origin, vec[3].t[0], vec[3].t[1], vec[3].t[2]);
	vector(&r.direction, vec[5].t[0], vec[5].t[1], vec[5].t[2]);
	return (r);
}
