/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:24:43 by aoshinth          #+#    #+#             */
/*   Updated: 2025/07/30 15:13:03 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

void	render(t_state *state)
{
	int		x;
	int		y;
	t_ray	r;
	t_tuple	c;

	y = 0;
	while (y < state->camera.vsize)
	{
		x = 0;
		while (x < state->camera.hsize)
		{
			r = ray_for_pixel(&state->camera, x, y);
			c = color_at(&state->world, &r);
			mlx_put_pixel(state->img, x, y, tuple_to_color(&c));
			x++;
		}
		y++;
	}
}

int	init_mlx_window(t_state *state)
{
	state->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!state->mlx)
		return (ft_error("Failed to initialize MLX."), 1);
	state->img = mlx_new_image(state->mlx, WIDTH, HEIGHT);
	if (!state->img)
	{
		mlx_terminate(state->mlx);
		return (ft_error("Failed to create image."), 1);
	}
	if (mlx_image_to_window(state->mlx, state->img, 0, 0) < 0)
	{
		mlx_delete_image(state->mlx, state->img);
		mlx_terminate(state->mlx);
		return (ft_error("Failed to attach image."), 1);
	}
	return (0);
}

int	render_image(t_state *state)
{
	state->camera.hsize = WIDTH;
	state->camera.vsize = HEIGHT;
	state->mlx = mlx_init(state->camera.hsize, state->camera.vsize,
			"MiniRT", true);
	if (!state->mlx)
		return (1);
	state->img = mlx_new_image(state->mlx, state->camera.hsize,
			state->camera.vsize);
	if (!state->img || mlx_image_to_window(state->mlx, state->img, 0, 0) < 0)
		return (1);
	render(state);
	mlx_key_hook(state->mlx, keypress, state);
	mlx_loop_hook(state->mlx, render_if_resized, state);
	mlx_loop(state->mlx);
	mlx_terminate(state->mlx);
	return (0);
}

void	keypress(mlx_key_data_t keydata, void *param)
{
	t_state	*state;

	state = (t_state *)param;
	if (keydata.action != MLX_PRESS)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
	{
		state->done = true;
		return ;
	}
	if (keydata.key == MLX_KEY_N)
	{
		select_next_object(state);
		return ;
	}
	if (!state->selected_object)
		return ;
	if (change_value(keydata, state->selected_object) == SUCCESS)
	{
		render(state);
		printf("✅ Updated object.\n");
	}
	else
		printf("⚠️ No change applied.\n");
}
