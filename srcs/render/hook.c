/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 20:49:45 by aoshinth          #+#    #+#             */
/*   Updated: 2025/08/04 05:29:02 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	window_resized(void *param)
{
	t_state			*state;
	int32_t			cur_w;
	int32_t			cur_h;
	static int32_t	prev_w = WIDTH;
	static int32_t	prev_h = HEIGHT;

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
	handle_window_resize(state, cur_w, cur_h);
}

void	keypress(mlx_key_data_t keydata, void *param)
{
	t_state	*state;
	bool	left;
	bool	right;

	state = (t_state *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		state->done = true;
	left = mlx_is_key_down(state->mlx, MLX_KEY_LEFT_CONTROL);
	right = mlx_is_key_down(state->mlx, MLX_KEY_RIGHT_CONTROL);
	if (keydata.key == MLX_KEY_L && (left || right))
		select_ligth_source(state);
	else if (keydata.key == MLX_KEY_N && (left || right))
		select_next_object(state);
	else if (keydata.key == MLX_KEY_E && (left || right))
		select_exit_interaction(state);
	else if (keydata.key == MLX_KEY_C && (left || right))
		select_camera(state);
	else if (keydata.key == MLX_KEY_H && state->interact == DEFAULT)
		help_menu();
	else if (state->interact != DEFAULT)
		select_mode(keydata, state);
}
