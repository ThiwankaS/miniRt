/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:42:55 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/23 06:37:00 by tsomacha         ###   ########.fr       */
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
	normal->t[3] = 0.0f;
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
	// v[0..2]: effective_color (r, g, b)
	// s[4]: material.diffuse
	// v[10]: light_dot_normal
	printf("before : \n");
	tuple_print(out);
	printf("v[0] : %.3f\n", v[0]);
	printf("v[1] : %.3f\n", v[1]);
	printf("v[2] : %.3f\n", v[2]);
	printf("s[4] : %.3f\n", s[4]);
	printf("v[10] : %.3f\n", v[10]);
	out->t[0] += v[0] * s[4] * v[10];
	out->t[1] += v[1] * s[4] * v[10];
	out->t[2] += v[2] * s[4] * v[10];
	printf("after : \n");
	tuple_print(out);
	// Prepare reflection vector and dot(reflectv, eyev)
	float neg_light_dot_normal = -(v[7] * s[16] + v[8] * s[17] + v[9] * s[18]);
	float reflect_scale = 2.0f * neg_light_dot_normal;

	float reflectv_x = -v[7] - reflect_scale * s[16];
	float reflectv_y = -v[8] - reflect_scale * s[17];
	float reflectv_z = -v[9] - reflect_scale * s[18];

	v[16] = reflectv_x * s[19] + reflectv_y * s[20] + reflectv_z * s[21];
}

void	cal_specular(t_tuple *out, float *s, float *v)
{
	// s[6]: shininess
	float factor = powf(v[16], s[6]);

	// s[5]: specular, s[7..9]: light color
	out->t[0] += s[7] * s[5] * factor;
	out->t[1] += s[8] * s[5] * factor;
	out->t[2] += s[9] * s[5] * factor;
}

void	cache_values(t_object *obj, t_light *light, t_compute *comp, float *s)
{
	// printf("obj->color\n");
	// tuple_print(&obj->color);
	// printf("light->color\n");
	// tuple_print(&light->color);
	// printf("light->position\n");
	// tuple_print(&light->position);
	// printf("comp->p\n");
	// tuple_print(&comp->p);
	// printf("comp->normal_v\n");
	// tuple_print(&comp->normal_v);
	// printf("comp->eye_v\n");
	// tuple_print(&comp->eye_v);
	// Object color and material properties
	s[0] = obj->color.t[0];    // red
	s[1] = obj->color.t[1];    // green
	s[2] = obj->color.t[2];    // blue
	s[3] = obj->ambient;
	s[4] = obj->diffuse;
	s[5] = obj->specular;
	s[6] = obj->shininess;

	// Light color and position
	s[7] = light->color.t[0];  // light red
	s[8] = light->color.t[1];  // light green
	s[9] = light->color.t[2];  // light blue
	s[10] = light->position.t[0];
	s[11] = light->position.t[1];
	s[12] = light->position.t[2];

	// Point of intersection and surface normal
	s[13] = comp->p.t[0];
	s[14] = comp->p.t[1];
	s[15] = comp->p.t[2];
	s[16] = comp->normal_v.t[0];
	s[17] = comp->normal_v.t[1];
	s[18] = comp->normal_v.t[2];

	// Eye vector
	s[19] = comp->eye_v.t[0];
	s[20] = comp->eye_v.t[1];
	s[21] = comp->eye_v.t[2];
}

void	lighting(t_tuple *out, t_object *obj, t_light *light, t_compute *comp)
{
	float s[22];  // cached values
	float v[19];  // working values

	cache_values(obj, light, comp, s);

	// Effective color = object color * light color
	float r = s[0] * s[7];
	float g = s[1] * s[8];
	float b = s[2] * s[9];

	// Start with ambient light
	out->t[0] = r * s[3];
	out->t[1] = g * s[3];
	out->t[2] = b * s[3];

	// Direction from point to light
	float lightv_x = s[10] - s[13];
	float lightv_y = s[11] - s[14];
	float lightv_z = s[12] - s[15];
	printf(" lightv_x: %.3f\n", lightv_x);
	printf(" lightv_y : %.3f\n", lightv_y);
	printf(" lightv_z: %.3f\n", lightv_z);
	float light_mag = sqrtf(lightv_x * lightv_x + lightv_y * lightv_y + lightv_z * lightv_z);
	printf(" light_mag : %.3f\n", light_mag);
	float lx = lightv_x / light_mag;
	float ly = lightv_y / light_mag;
	float lz = lightv_z / light_mag;
	printf(" lx : %.3f\n", lx);
	printf(" ly : %.3f\n", ly);
	printf(" lz : %.3f\n", lz);
	float light_dot_normal = lx * s[16] + ly * s[17] + lz * s[18];
	printf(" light_dot_normal : %.3f\n", light_dot_normal);
	// Store for diffuse and reflection
	v[0] = r;
	v[1] = g;
	v[2] = b;
	v[7] = lx;
	v[8] = ly;
	v[9] = lz;
	v[10] = light_dot_normal;
	printf("lightv: %.3f %.3f %.3f | dot: %.3f\n",
    lightv_x, lightv_y, lightv_z, light_dot_normal);
	if (light_dot_normal >= 0.0f)
	{
		// printf("light_dot_normal : %.3f\n", light_dot_normal);
		cal_diffuse(out, s, v);
		// if (v[16] > 0.0f)
		// 	cal_specular(out, s, v);
	}
	out->t[3] = 1.0f; // Alpha
}
