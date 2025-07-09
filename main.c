# include "include/miniRt.h"

# define WIDTH  1600
# define HEIGHT 1200

int main(void)
{
	uint32_t color = 0xFF0000FF;

	// Create window and image
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "My Window", true);
	if (!mlx)
		return 1;

	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return 1;

	// SHOW THE IMAGE FIRST!
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return 1;

	float light_x = 0, light_y = 0, light_z = -5;
	float wall_x, wall_y, wall_z = 10.0;
	float wall_size = 10.0;
	int width = 300, height = 300;
	float pixel_size = wall_size / width;

	//seting up the sphere
	t_object s;
	s.id = 1;
	s.material = NULL;
	s.radius = 1.0;
	s.type = 1;
	s.x = 0.0;
	s.y = 0.0;
	s.z = 0.0;
	indentity(&s.transform);

	//setting up the ray
	t_ray r;
	point(&r.origin, light_x, light_y, light_z);

	t_tuple p, temp;
	t_intersect *xs;

	for(int y = 0; y < (height -1); y++)
	{
		wall_y = (wall_size / 2) - (pixel_size * y);
		for(int x = 0; x <(width - 1); x++)
		{
			wall_x = (pixel_size * x) - (wall_size / 2);
			point(&p, wall_x, wall_y, wall_z);
			tuple_subtract(&temp, &p, &r.origin);
			normalize(&r.direction, &temp);
			xs = calculate_intersects(&s, &r);
			if(xs && (xs[0].value >= 0 || xs[1].value >= 0))
				mlx_put_pixel(img, x, y, color);
			free(xs);
		}
	}
	// Keep window open
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
