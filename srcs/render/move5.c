/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 08:43:51 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/04 06:19:09 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

t_tuple	camera_position(t_camera *camera);
t_tuple	camera_direction(t_camera *camera, t_tuple *pos);

int	rotate_camera(mlx_key_data_t key, t_state *state)
{
	t_tuple	pos;
	t_tuple	dir;
	t_mat	rotate;

	pos = camera_position(&state->camera);
	dir = camera_direction(&state->camera, &pos);
	if (key.key == MLX_KEY_W)
		rotate = rotate_y(0.1f);
	else if (key.key == MLX_KEY_S)
		rotate = rotate_y(-0.1f);
	else if (key.key == MLX_KEY_A)
		rotate = rotate_x(0.1f);
	else if (key.key == MLX_KEY_D)
		rotate = rotate_x(-0.1f);
	else if (key.key == MLX_KEY_Z)
		rotate = rotate_z(0.1f);
	else if (key.key == MLX_KEY_X)
		rotate = rotate_z(-0.1f);
	else
		return (FAILURE);
	dir = matrix_multiply_by_tuple(&rotate, &dir);
	dir = normalize(&dir);
	update_view(&state->camera, &pos, &dir);
	return (SUCCESS);
}

int	move_camera(mlx_key_data_t key, t_state *state)
{
	t_tuple	pos;
	t_tuple	dir;
	float	step;

	pos = camera_position(&state->camera);
	dir = camera_direction(&state->camera, &pos);
	step = 0.1f;
	if (key.key == MLX_KEY_W)
		pos.t[1] += step;
	else if (key.key == MLX_KEY_S)
		pos.t[1] -= step;
	else if (key.key == MLX_KEY_A)
		pos.t[0] -= step;
	else if (key.key == MLX_KEY_D)
		pos.t[0] += step;
	else if (key.key == MLX_KEY_Z)
		pos.t[2] += step;
	else if (key.key == MLX_KEY_X)
		pos.t[2] -= step;
	else
		return (FAILURE);
	update_view(&state->camera, &pos, &dir);
	return (SUCCESS);
}

int	zoom_camera(mlx_key_data_t key, t_state *state)
{
	float	step;

	step = 0.1f;
	if (key.key == MLX_KEY_A)
		state->camera.fov = fminf((float)M_PI, state->camera.fov + step);
	else if (key.key == MLX_KEY_D)
		state->camera.fov = fmaxf(0.1f, state->camera.fov - step);
	else
		return (FAILURE);
	update_fov(&state->camera, state->camera.fov);
	return (SUCCESS);
}

void	camera_interaction(mlx_key_data_t keydata, t_state *state)
{
	if (state->mode == DEFAULT)
		return ;
	if (state->mode == ROTATE && rotate_camera(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update camera !\n");
	}
	if (state->mode == MOVE && move_camera(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update camera !\n");
	}
	if (state->mode == ZOOM && zoom_camera(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update camera !\n");
	}
}

void	camera_interaction_mode(mlx_key_data_t keydata, t_state *state)
{
	bool	left;
	bool	right;

	if (state->interact == DEFAULT && state->mode == DEFAULT)
		return ;
	left = mlx_is_key_down(state->mlx, MLX_KEY_LEFT_CONTROL);
	right = mlx_is_key_down(state->mlx, MLX_KEY_RIGHT_CONTROL);
	if (keydata.key == MLX_KEY_M && (left || right))
	{
		state->mode = MOVE;
		printf("you can move the camera\n");
	}
	else if (keydata.key == MLX_KEY_S && (left || right))
	{
		state->mode = ROTATE;
		printf("you can rotate the camera\n");
	}
	else if (keydata.key == MLX_KEY_F && (left || right))
	{
		state->mode = ZOOM;
		printf("you can zoom the camera\n");
	}
	else if (keydata.key == MLX_KEY_H)
		help_camera();
	camera_interaction(keydata, state);
}
