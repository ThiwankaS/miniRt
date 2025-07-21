/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:42:55 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/16 12:47:54 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	normal_at(t_tuple *normal, t_object *s, t_tuple *world_point)
{
	t_tuple	obj_p;
	t_tuple	obj_nml;
	t_tuple	world_normal;
	float	dist;

	matrix_multiply_by_tuple(&obj_p, &s->invs, world_point);
	if (s->type == PLANE)
		vector(&obj_nml, 0.0f, 1.0f, 0.0f);
	else if (s->type == SPHERE)
		vector(&obj_nml, obj_p.t[0], obj_p.t[1], obj_p.t[2]);
	else if (s->type == CYLINDER)
	{
		dist = obj_p.t[0] * obj_p.t[0] + obj_p.t[2] * obj_p.t[2];
		if (dist < 1.0f && obj_p.t[1] >= 0.99f)
			vector(&obj_nml, 0, 1, 0);
		else if (dist < 1.0f && obj_p.t[1] <= -0.99f)
			vector(&obj_nml, 0, -1, 0);
		else
			vector(&obj_nml, obj_p.t[0], 0, obj_p.t[2]);
	}
	matrix_multiply_by_tuple(&world_normal, &s->invs_trans, &obj_nml);
	world_normal.t[3] = 0.0f;
	normalize(normal, &world_normal);
}

void	reflect(t_tuple *out, t_tuple *in, t_tuple *normal)
{
	float	product;

	product = 2.0f * dot(in, normal);
	out->t[0] = in->t[0] - normal->t[0] * product;
	out->t[1] = in->t[1] - normal->t[1] * product;
	out->t[2] = in->t[2] - normal->t[2] * product;
	out->t[3] = 0.0f;
}

void	cal_diffuse(t_tuple *out, float *s, float *v)
{
	out->t[0] += v[0] * s[4] * v[10];
	out->t[1] += v[1] * s[4] * v[10];
	out->t[2] += v[2] * s[4] * v[10];
	v[11] = -(v[7] * s[16] + v[8] * s[17] + v[9] * s[18]);
	v[12] = 2.0f * v[11];
	v[13] = -v[7] - v[12] * s[16];
	v[14] = -v[8] - v[12] * s[17];
	v[15] = -v[9] - v[12] * s[18];
	v[16] = v[13] * s[19] + v[14] * s[20] + v[15] * s[21];
}

void	cal_specular(t_tuple *out, float *s, float *v)
{
	v[18] = powf(v[16], s[6]);
	out->t[0] += s[7] * s[5] * v[18];
	out->t[1] += s[8] * s[5] * v[18];
	out->t[2] += s[9] * s[5] * v[18];
}

void	cache_values(t_material *m, t_light *light, t_compute *comp, float *s)
{
	s[0] = m->color.t[0];
	s[1] = m->color.t[1];
	s[2] = m->color.t[2];
	s[3] = m->ambient;
	s[4] = m->diffuse;
	s[5] = m->specular;
	s[6] = m->shininess;
	s[7] = light->color.t[0];
	s[8] = light->color.t[1];
	s[9] = light->color.t[2];
	s[10] = light->position.t[0];
	s[11] = light->position.t[1];
	s[12] = light->position.t[2];
	s[13] = comp->p.t[0];
	s[14] = comp->p.t[1];
	s[15] = comp->p.t[2];
	s[16] = comp->normal_v.t[0];
	s[17] = comp->normal_v.t[1];
	s[18] = comp->normal_v.t[2];
	s[19] = comp->eye_v.t[0];
	s[20] = comp->eye_v.t[1];
	s[21] = comp->eye_v.t[2];
}

void	lighting(t_tuple *out, t_material *m, t_light *light, t_compute *comp)
{
	float	v[19];
	float	s[22];

	cache_values(m, light, comp, s);
	v[0] = s[0] * s[7];
	v[1] = s[1] * s[8];
	v[2] = s[2] * s[9];
	out->t[0] = v[0] * s[3];
	out->t[1] = v[1] * s[3];
	out->t[2] = v[2] * s[3];
	v[3] = s[10] - s[13];
	v[4] = s[11] - s[14];
	v[5] = s[12] - s[15];
	v[6] = sqrtf(v[3] * v[3] + v[4] * v[4] + v[5] * v[5]);
	v[7] = v[3] / v[6];
	v[8] = v[4] / v[6];
	v[9] = v[5] / v[6];
	v[10] = v[7] * s[16] + v[8] * s[17] + v[9] * s[18];
	if (v[10] >= 0.0f)
	{
		cal_diffuse(out, s, v);
		if (v[16] > 0.0f)
			cal_specular(out, s, v);
	}
	out->t[3] = 1.0f;
}
