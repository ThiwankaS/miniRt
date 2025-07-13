# include "include/miniRt.h"

# define WIDTH   800
# define HEIGHT  600

int main(void)
{
		// Create window and image
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "My Window", true);
	if (!mlx)
		return (1);

	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (1);

	// SHOW THE IMAGE FIRST!
	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (1);

	t_world world;

	t_object *s1, *s2;

	s1 = ft_calloc(1, sizeof(t_object));
	s2 = ft_calloc(1, sizeof(t_object));

	t_material mat1, mat2;
	t_mat m1, m2, m3;

	mat1.ambient = 0.1f;
	mat1.diffuse = 0.7f;
	mat1.specular = 0.0f;
	mat1.shininess = 200.0f;
	color(&mat1.color, 0.0f, 0.0f, 1.0f);
	scaling(&m1, 0.3f, 0.3f, 0.3f);
	translation(&m2, -0.6f, 0.0f, 0.0f);
	matrix_multiply(&m3, &m2, &m1);
	s1->id = 1;
	s1->type = 1;
	s1->x = -0.6f;
	s1->y = 0.0f;
	s1->z = 0.0f;
	s1->radius = 1.0f;
	s1->material = &mat1;
	set_transform(&s1->transform, &m3);
	matrix_inverse(&s1->invs, &s1->transform);


	mat2.ambient = 0.1f;
	mat2.diffuse = 0.7f;
	mat2.specular = 0.0f;
	mat2.shininess = 200.0f;
	color(&mat2.color, 1.0f, 0.0f, 0.0f);
	scaling(&m1, 0.3f, 0.3f, 0.3f);
	translation(&m2, 0.6f, 0.0f, 0.0f);
	matrix_multiply(&m3, &m2, &m1);
	s2->id = 2;
	s2->type = 1;
	s2->x = 0.6f;
	s2->y = 0.0f;
	s2->z = 0.0f;
	s2->radius = 1.0f;
	s2->material = &mat2;
	set_transform(&s2->transform, &m3);
	matrix_inverse(&s2->invs, &s2->transform);

	s1->next = s2;
	s2->next = NULL;

	point(&world.light.position, -10.0f, 10.0f, -10.0f);
	color(&world.light.color, 1.0f, 1.0f, 1.0f);
	world.components = s1;

	t_camera *camera = camera_init(WIDTH, HEIGHT, M_PI / 3);
	t_tuple from, to, up;
	point(&from, 1.0f, 1.0f, 1.0f);
	point(&to, 0.0f, 0.0f, 0.0f);
	vector(&up, 0.0f, 1.0f, 0.0f);
	view_transformation(camera, &from, &to, &up);

	render(img, camera, &world);

	free(camera);
	free(s1);
	free(s2);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}
