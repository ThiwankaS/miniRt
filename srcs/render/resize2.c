/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 05:53:40 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/03 06:44:22 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Resizes the sphere with arrow keys (UP increases, DOWN decreases).
 * Rebuilds its transform after change.
 * Returns SUCCESS on handled key, otherwise FAILURE.
*/
int	resize_sphere(mlx_key_data_t key, t_object *obj)
{
	float	step;

	step = 0.05f;
	if (!obj)
		return (FAILURE);
	if (key.key == MLX_KEY_UP)
		obj->radius = obj->radius + step;
	else if (key.key == MLX_KEY_DOWN)
		obj->radius = fmaxf(0.5f, obj->radius - step);
	else
		return (FAILURE);
	creating_sphere_object(obj, obj->radius);
	return (SUCCESS);
}

/**
 * Moves the sphere by small steps with W/A/S/D/Z/X keys.
 * Rebuilds its transform after a successful move.
 * Returns SUCCESS on handled key, otherwise FAILURE.
*/
int	move_sphere(mlx_key_data_t key, t_object *obj)
{
	float	step;

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
	creating_sphere_object(obj, obj->radius);
	return (SUCCESS);
}
