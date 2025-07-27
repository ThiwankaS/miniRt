/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:42:55 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/27 07:22:21 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

t_tuple	normal_at(t_object *s, t_tuple *world_point)
{
	t_tuple normal;
	t_tuple	obj_point;
	t_tuple	obj_normal;
	t_tuple	world_normal;
	t_tuple absolute_point;
	//float	dist;

	point(&absolute_point, 0.0f, 0.0f, 0.0f);
	obj_point = matrix_multiply_by_tuple(&s->invs, world_point);
	/* if (s->type == PLANE)
		vector(&obj_normal, 0.0f, 1.0f, 0.0f);
	else if (s->type == SPHERE)
		tuple_subtract(&obj_normal, &obj_point, &absolute_point);
	else if (s->type == CYLINDER)
	{
		dist = obj_point.t[0] * obj_point.t[0] + obj_point.t[2] * obj_point.t[2];
		if (dist < 1.0f && obj_point.t[1] >= 0.99f)
			vector(&obj_normal, 0, 1, 0);
		else if (dist < 1.0f && obj_point.t[1] <= -0.99f)
			vector(&obj_normal, 0, -1, 0);
		else
			vector(&obj_normal, obj_point.t[0], 0, obj_point.t[2]);
	} */
	obj_normal = tuple_subtract(&obj_point, &absolute_point);//this only work for sphere need to uncomment
	world_normal = matrix_multiply_by_tuple(&s->invs_trans, &obj_normal);
	world_normal.t[3] = 0.0f;
	normal = normalize(&world_normal);
	return normal;
}

t_tuple reflect(t_tuple *in, t_tuple *normal)
{
	t_tuple	reflect;
	t_tuple temp;
	float	product;

	product = 2.0f * dot(in, normal);
	temp = tuple_multiply_scalar(normal, product);
	reflect = tuple_subtract(in, &temp);
	return reflect;
}

t_tuple	lighting(t_object *obj, t_light *light, t_compute *comp)
{
	t_tuple colour;
	t_tuple ambient;
	t_tuple diffuse;
	t_tuple specular;
	t_tuple effective_color;
	t_tuple lightv;
	t_tuple reflectv;
	t_tuple temp;
	t_tuple neg;
	float light_dot_normal;
	float reflect_dot_eye;
	float factor;

	// Compute effective color = obj color * light intensity
	effective_color = schur_product(&obj->color, &light->color);

	// Compute light direction vector
	temp = tuple_subtract(&light->position, &comp->p);
	lightv = normalize(&temp);

	// AMBIENT = effective_color * ambient coefficient
	ambient = tuple_multiply_scalar(&effective_color, obj->ambient);

	// light_dot_normal = dot(lightv, normalv)
	light_dot_normal = dot(&lightv, &comp->normal_v);
	if (light_dot_normal < 0.0f)
	{
		color(&diffuse, 0, 0, 0);
		color(&specular, 0, 0, 0);
	}
	else
	{
		// DIFFUSE = effective_color * diffuse coefficient * light_dot_normal
		diffuse = tuple_multiply_scalar(&effective_color, obj->diffuse * light_dot_normal);

		// REFLECT = reflect(-lightv, normalv)
		neg = tuple_negate(&lightv);
		reflectv = reflect(&neg, &comp->normal_v);

		// reflect_dot_eye = dot(reflectv, eyev)
		reflect_dot_eye = dot(&reflectv, &comp->eye_v);

		if (reflect_dot_eye <= 0.0f)
			color(&specular, 0, 0, 0);
		else
		{
			factor = powf(reflect_dot_eye, obj->shininess);
			specular = tuple_multiply_scalar(&light->color, obj->specular * factor);
		}
	}
	colour.t[0] = ambient.t[0] + diffuse.t[0] + specular.t[0];
	colour.t[1] = ambient.t[1] + diffuse.t[1] + specular.t[1];
	colour.t[2] = ambient.t[2] + diffuse.t[2] + specular.t[2];
	colour.t[0] = fminf(1.0f, colour.t[0]);
	colour.t[1] = fminf(1.0f, colour.t[1]);
	colour.t[2] = fminf(1.0f, colour.t[2]);
	colour.t[3] = 1.0f;
	return colour;
}
