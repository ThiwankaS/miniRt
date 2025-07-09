# include "include/miniRt.h"

typedef struct s_projectile
{
	t_tuple point;
	t_tuple velocity;
} t_projectile;

typedef struct s_environment
{
	t_tuple gravity;
	t_tuple wind;
} t_environment;

t_projectile *tick(t_environment *e, t_projectile *p);

// WIDTH and HEIGHT
#define WIDTH 1600
#define HEIGHT 1200

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

	// Setup tuples
	t_tuple p, velocity, gravity, wind, norm_velocity, scaled_velocity;

	point(&p, 50.0, 50.0, 0.0); // start 1 unit up so it's visible
	vector(&velocity, 1.0, 1.8, 0.0);
	normalize(&norm_velocity, &velocity);
	tuple_multiply_scalor(&scaled_velocity, &norm_velocity, 15.0); // reasonable speed

	vector(&gravity, 0.0, -0.1, 0.0);
	vector(&wind, -0.01, 0.0, 0.0);

	t_projectile proj = {p, scaled_velocity};
	t_environment env = {gravity, wind};

	// Draw the motion
	while (proj.point.t[1] > 0 && proj.point.t[0] >= 0 && proj.point.t[0] < WIDTH && proj.point.t[1] < HEIGHT)
	{
		int x = (int)proj.point.t[0];
		int y = HEIGHT - (int)proj.point.t[1]; // Flip Y axis

		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
			mlx_put_pixel(img, x, y, color);

		t_projectile *next = tick(&env, &proj);
		proj = *next;
		free(next);
	}

	// Keep window open
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}

t_projectile *tick(t_environment *e, t_projectile *p)
{
	t_projectile *pro = malloc(sizeof(t_projectile));
	t_tuple temp;

	tuple_add(&pro->point, &p->point, &p->velocity);
	tuple_add(&temp, &e->gravity, &e->wind);
	tuple_add(&pro->velocity, &p->velocity, &temp);

	return pro;
}
