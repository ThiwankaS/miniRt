/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:42:55 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/11 04:21:56 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	normal_at(t_tuple *normal, t_object *s, t_tuple *world_point)
{
	t_mat	inverse;
	t_mat	trans;
	t_tuple	abs;
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	if (!matrix_inverse(&inverse, &s->transform))
	{
		vector(normal, 0, 0, 0);
		return ;
	}
	point(&abs, 0, 0, 0);
	matrix_multiply_by_tuple(&object_point, &inverse, world_point);
	tuple_subtract(&object_normal, &object_point, &abs);
	matrix_transpose(&trans, &inverse);
	matrix_multiply_by_tuple(&world_normal, &trans, &object_normal);
	world_normal.t[3] = 0.0f;
	normalize(normal, &world_normal);
}

void	reflect(t_tuple *out, t_tuple *in, t_tuple *normal)
{
	float	product;
	t_tuple	scaled;

	product = dot(in, normal) * 2.0f;
	tuple_multiply_scalor(&scaled, normal, product);
	tuple_subtract(out, in, &scaled);
}

void	point_light(t_light *light, t_tuple *position, t_tuple *intensity)
{
	light->color = *intensity;
	light->position = *position;
}

void	lighting(t_tuple *out, t_material *m, t_light *light, t_tuple *position, t_tuple *eye, t_tuple *normal)
{
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	t_tuple	effective_color;
	t_tuple	lightv;
	t_tuple	neg_lightv;
	t_tuple	reflectv;
	t_tuple	temp;
	float	light_dot_normal;
	float	reflect_dot_eye;
	float	factor;

	schur_product(&effective_color, &m->color, &light->color);
	tuple_subtract(&temp, &light->position, position);
	normalize(&lightv, &temp);
	tuple_multiply_scalor(&ambient, &effective_color, m->ambient);
	light_dot_normal = dot(&lightv, normal);
	if (light_dot_normal < 0.0f)
	{
		color(&diffuse, 0.0f, 0.0f, 0.0f);
		color(&specular, 0.0f, 0.0f, 0.0f);
	}
	else
	{
		tuple_multiply_scalor(&diffuse, &effective_color, light_dot_normal * m->diffuse);
		tuple_negate(&neg_lightv, &lightv);
		reflect(&reflectv, &neg_lightv, normal);
		reflect_dot_eye = dot(&reflectv, eye);
		if (reflect_dot_eye <= 0.0f)
			vector(&specular, 0.0f, 0.0f, 0.0f);
		else
		{
			factor = pow(reflect_dot_eye, m->shininess);
			tuple_multiply_scalor(&specular, &light->color, m->specular * factor);
		}
	}
	tuple_add(&temp, &ambient, &diffuse);
	tuple_add(out, &temp, &specular);
	out->t[3] = 1.0f;
}
