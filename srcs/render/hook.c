/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:49:45 by aoshinth          #+#    #+#             */
/*   Updated: 2025/07/30 11:35:23 by aoshinth         ###   ########.fr       */
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
	static int32_t	prev_w = WIDTH;
	static int32_t	prev_h = HEIGHT;
	int32_t			cur_w;
	int32_t			cur_h;

	state = (t_state *)param;
	if (state->done)
	{
		if (state->img)
			mlx_delete_image(state->mlx, state->img);
		if (state->mlx)
			mlx_close_window(state->mlx);
		return ;
	}
	cur_w = state->mlx->width;
	cur_h = state->mlx->height;
	if (cur_w == prev_w && cur_h == prev_h)
		return ;
	prev_w = cur_w;
	prev_h = cur_h;
	handle_resize(state, cur_w, cur_h);
}

void	setup_hooks(t_state *state)
{
	mlx_close_hook(state->mlx, close_hook, state);
	mlx_key_hook(state->mlx, keypress, state);
	mlx_loop_hook(state->mlx, render_if_resized, state);
}
