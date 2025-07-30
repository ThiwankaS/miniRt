#include "../../include/miniRt.h"

void	render(t_state *state)
{
	int		x, y;
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

	state->mlx = mlx_init(state->camera.hsize, state->camera.vsize, "MiniRT", true);
	if (!state->mlx)
		return (1);

	state->img = mlx_new_image(state->mlx, state->camera.hsize, state->camera.vsize);
	if (!state->img || mlx_image_to_window(state->mlx, state->img, 0, 0) < 0)
		return (1);

	render(state);

	mlx_loop_hook(state->mlx, render_if_resized, state);
	mlx_loop(state->mlx);
	mlx_terminate(state->mlx);
	return (0);
}
