#include "../../include/miniRt.h"

void	render(t_state *state)
{
	int		x;
	int		y;
	t_ray	r;
	t_tuple	c;

	y = 0;
	//	print_things(state);
	while(y < HEIGHT)
	{
		x = 0;
		while(x < WIDTH)
		{
			r = ray_for_pixel(&state->camera, x, y);
			c = color_at(&state->world, &r);
			mlx_put_pixel(state->img, x, y, tuple_to_color(&c));
			x++;
		}
		y++;
	}
}

int	render_image(t_state *state)
{
	state->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	if (!state->mlx)
		return (1);
	state->img = mlx_new_image(state->mlx, WIDTH, HEIGHT);
	if (!state->img || mlx_image_to_window(state->mlx, state->img, 0, 0) < 0)
		return (1);
	render(state);
	mlx_loop(state->mlx);
	mlx_terminate(state->mlx);
	return (0);
}
