/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 05:53:40 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/02 15:48:32 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

int	resize_sphere(mlx_key_data_t key, t_object *obj)
{
	float	step;
	t_mat	m1;
	t_mat	m2;

	step = 0.05f;
	if (!obj)
		return (FAILURE);
	if (key.key == MLX_KEY_UP)
		obj->radius = obj->radius + step;
	else if (key.key == MLX_KEY_DOWN)
		obj->radius = fmaxf(1.0f, obj->radius - step);
	else
		return (FAILURE);
	m1 = translation(obj->x, obj->y, obj->y);
	m2 = scaling(obj->radius, obj->radius, obj->radius);
	obj->transform = matrix_multiply(&m1, &m2);
	matrix_inverse(&obj->invs, &obj->transform);
	obj->invs_trans = matrix_transpose(&obj->invs);
	return (SUCCESS);
}

int	move_sphere(mlx_key_data_t key, t_object *obj)
{
	float	step;
	t_mat	m1;
	t_mat	m2;

	step = 0.1f;
	if (key.key == MLX_KEY_W)
		obj->y += step;
	else if (key.key == MLX_KEY_S)
		obj->y -= step;
	else if (key.key == MLX_KEY_A)
		obj->x -= step;
	else if (key.key == MLX_KEY_D)
		obj->x += step;
	else if (key.key == MLX_KEY_Z)
		obj->z += step;
	else if (key.key == MLX_KEY_X)
		obj->z -= step;
	else
		return (FAILURE);
	m1 = translation(obj->x, obj->y, obj->z);
	m2 = scaling(obj->radius, obj->radius, obj->radius);
	obj->transform = matrix_multiply(&m1, &m2);
	matrix_inverse(&obj->invs, &obj->transform);
	obj->invs_trans = matrix_transpose(&obj->invs);
	return (SUCCESS);
}
