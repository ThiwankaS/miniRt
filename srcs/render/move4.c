/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 08:43:51 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/04 06:10:26 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

int	rotate_plane(mlx_key_data_t key, t_object *obj)
{
	float	angle;
	t_mat	rotate;

	angle = 0.1f;
	if (key.key == MLX_KEY_W)
		rotate = rotate_y(angle);
	else if (key.key == MLX_KEY_S)
		rotate = rotate_y(-angle);
	else if (key.key == MLX_KEY_A)
		rotate = rotate_x(angle);
	else if (key.key == MLX_KEY_D)
		rotate = rotate_x(-angle);
	else if (key.key == MLX_KEY_Z)
		rotate = rotate_z(angle);
	else if (key.key == MLX_KEY_X)
		rotate = rotate_z(-angle);
	else
		return (FAILURE);
	obj->norm_v = matrix_multiply_by_tuple(&rotate, &obj->norm_v);
	obj->norm_v = normalize(&obj->norm_v);
	creating_plane_object(obj);
	return (SUCCESS);
}

void	plane_interaction(mlx_key_data_t key, t_state *state)
{
	t_object	*selected;

	selected = state->selected_object;
	if (state->mode == DEFAULT || !selected)
		return ;
	if (state->mode == ROTATE && rotate_plane(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
}

t_tuple	camera_position(t_camera *camera)
{
	t_tuple	origin;

	point(&origin, 0.0f, 0.0f, 0.0f);
	return (matrix_multiply_by_tuple(&camera->invs, &origin));
}

t_tuple	camera_direction(t_camera *camera, t_tuple *pos)
{
	t_tuple	look_at;
	t_tuple	dir;

	point(&look_at, 0.0f, 0.0f, -1.0f);
	look_at = matrix_multiply_by_tuple(&camera->invs, &look_at);
	dir = tuple_subtract(&look_at, pos);
	return (normalize(&dir));
}
