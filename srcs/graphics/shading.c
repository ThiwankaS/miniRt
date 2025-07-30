/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 05:42:55 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 08:24:56 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

t_tuple	reflect(t_tuple *in, t_tuple *normal)
{
	t_tuple	reflect;
	t_tuple	temp;
	float	product;

	product = 2.0f * dot(in, normal);
	temp = tuple_multiply_scalar(normal, product);
	reflect = tuple_subtract(in, &temp);
	return (reflect);
}

t_tuple	final_color(t_tuple *ambient, t_tuple *diffuse, t_tuple *specular)
{
	t_tuple	colour;

	colour.t[0] = ambient->t[0] + diffuse->t[0] + specular->t[0];
	colour.t[1] = ambient->t[1] + diffuse->t[1] + specular->t[1];
	colour.t[2] = ambient->t[2] + diffuse->t[2] + specular->t[2];
	colour.t[0] = fminf(1.0f, colour.t[0]);
	colour.t[1] = fminf(1.0f, colour.t[1]);
	colour.t[2] = fminf(1.0f, colour.t[2]);
	colour.t[3] = 1.0f;
	return (colour);
}

t_tuple	spec_color(t_object *obj, t_light *light, t_compute *comp, t_tuple *lv)
{
	t_tuple	reflectv;
	t_tuple	neg;
	t_tuple	specular;
	float	reflect_dot_eye;
	float	f;

	neg = tuple_negate(lv);
	reflectv = reflect(&neg, &comp->normal_v);
	reflect_dot_eye = dot(&reflectv, &comp->eye_v);
	if (reflect_dot_eye <= 0.0f)
		color(&specular, 0, 0, 0);
	else
	{
		f = powf(reflect_dot_eye, obj->shininess);
		specular = tuple_multiply_scalar(&light->color, obj->specular * f);
	}
	return (specular);
}

t_tuple	lighting(t_object *obj, t_light *light, t_compute *comp)
{
	t_tuple	ambient;
	t_tuple	diffuse;
	t_tuple	specular;
	t_tuple	vec[3];
	float	product;

	vec[0] = schur_product(&obj->color, &light->color);
	vec[1] = tuple_subtract(&light->position, &comp->over_p);
	vec[2] = normalize(&vec[1]);
	ambient = tuple_multiply_scalar(&vec[0], obj->ambient);
	product = dot(&vec[2], &comp->normal_v);
	if (product < 0.0f || comp->shadowed)
	{
		color(&diffuse, 0, 0, 0);
		color(&specular, 0, 0, 0);
	}
	else
	{
		diffuse = tuple_multiply_scalar(&vec[0], obj->diffuse * product);
		specular = spec_color(obj, light, comp, &vec[2]);
	}
	return (final_color(&ambient, &diffuse, &specular));
}
