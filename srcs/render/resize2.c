/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 05:53:40 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/31 05:59:44 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

int	resize_sphere(mlx_key_data_t key, t_object *obj)
{
	if (!obj)
		return (FAILURE);
	if (key.key == MLX_KEY_UP)
		obj->radius += 0.1f;
	else if (key.key == MLX_KEY_DOWN)
		obj->radius = fmaxf(0.1f, obj->radius - 0.1f);
	return (SUCCESS);
}

int	resize_cylinder(mlx_key_data_t key, t_object *obj)
{
	if (!obj)
		return (FAILURE);
	if (key.key == MLX_KEY_UP)
		obj->radius += 0.1f;
	if (key.key == MLX_KEY_DOWN)
		obj->radius = fmaxf(0.1f, obj->radius - 0.1f);
	if (key.key == MLX_KEY_RIGHT)
		obj->height += 0.1f;
	if (key.key == MLX_KEY_LEFT)
		obj->height = fmaxf(0.1f, obj->height - 0.1f);
	return (SUCCESS);
}
