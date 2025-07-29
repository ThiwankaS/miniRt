/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:49:45 by aoshinth          #+#    #+#             */
/*   Updated: 2025/07/29 21:53:20 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	uninit_mlx(t_state *state)
{
	if (state->img)
		mlx_delete_image(state->mlx, state->img);
	if (state->mlx)
		mlx_terminate(state->mlx);
	exit(0);
}

void	close_hook(void *ptr)
{
	uninit_mlx((t_state *)ptr);
}

void	key_hook(mlx_key_data_t k_data, void *ptr)
{
	if (k_data.key == MLX_KEY_ESCAPE && k_data.action == MLX_PRESS)
		close_hook(ptr);
}

void	render_if_resized(void *param)
{
	t_state			*state;
	static int32_t	prev_width = WIDTH;
	static int32_t	prev_height = HEIGHT;
	int32_t			cur_width;
	int32_t			cur_height;

	state = (t_state *)param;
	cur_width = state->mlx->width;
	cur_height = state->mlx->height;
	if (cur_width != prev_width || cur_height != prev_height)
	{
		prev_width = cur_width;
		prev_height = cur_height;
		state->camera.hsize = cur_width;
		state->camera.vsize = cur_height;
		update_fov(&state->camera, state->camera.fov);
		if (state->img)
			mlx_delete_image(state->mlx, state->img);
		state->img = mlx_new_image(state->mlx, cur_width, cur_height);
		mlx_image_to_window(state->mlx, state->img, 0, 0);
		render(state);
	}
}

void	setup_hooks(t_state *state)
{
	mlx_close_hook(state->mlx, close_hook, state);
	mlx_key_hook(state->mlx, key_hook, state);
	mlx_loop_hook(state->mlx, render_if_resized, state);
}