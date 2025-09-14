/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 10:24:43 by aoshinth          #+#    #+#             */
/*   Updated: 2025/08/04 05:26:20 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Traces a ray through every pixel of the camera viewport and writes the
 * computed color into the MLX image. Mutates state->img in place.
 */
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

/**
 * Creates the MLX window and backing image at WIDTH x HEIGHT and attaches the
 * image to the window. Prints an error and cleans up on failure;
 * returns nonzero on error.
 */
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

/**
 * Initializes MLX using the camera’s current hsize/vsize, creates and displays
 * the image, renders the scene once, sets input/resize hooks,
 * and runs the MLX loop.
 * Returns nonzero if initialization or image setup fails.
 */
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
	mlx_loop_hook(state->mlx, window_resized, state);
	mlx_loop(state->mlx);
	mlx_terminate(state->mlx);
	return (0);
}
