/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 23:00:00 by aoshinth          #+#    #+#             */
/*   Updated: 2025/07/30 07:34:27 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/miniRt.h"

int	resize_object(mlx_key_data_t key, t_object *obj)
{
	if (!obj)
		return (FAILURE);
	if (obj->type == SPHERE || obj->type == CYLINDER)
	{
		if (key.key == MLX_KEY_UP)
			obj->radius += 0.1f;
		else if (key.key == MLX_KEY_DOWN)
			obj->radius = fmaxf(0.1f, obj->radius - 0.1f);
	}
	if (obj->type == CYLINDER)
	{
		if (key.key == MLX_KEY_RIGHT)
			obj->height += 0.1f;
		else if (key.key == MLX_KEY_LEFT)
			obj->height = fmaxf(0.1f, obj->height - 0.1f);
	}
	return (SUCCESS);
}

int	change_value(mlx_key_data_t keydata, t_object *selected)
{
	if (!selected)
		return (FAILURE);
	if (selected->type == SPHERE || selected->type == CYLINDER)
		return (resize_object(keydata, selected));
	return (FAILURE);
}











