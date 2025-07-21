#include "include/miniRt.h"
#define WIDTH 1600
#define HEIGHT 1200

int	main(void)
{
	mlx_t *mlx = mlx_init(WIDTH, HEIGHT, "MiniRT Corner Room", true);
	if (!mlx)
		return (1);
	mlx_image_t *img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!img || mlx_image_to_window(mlx, img, 0, 0) < 0)
		return (1);

	t_world world;
	t_material m_wall, m_sphere1, m_sphere2, m_cylinder;
	t_object floor, left_wall, back_wall, sphere1, sphere2, cylinder;
	t_mat scale, trans, rot, tmp;

	// Common wall material
	color(&m_wall.color, 0.8f, 0.8f, 1.0f);
	m_wall.ambient = 0.2f; m_wall.diffuse = 0.8f;
	m_wall.specular = 0.0f; m_wall.shininess = 10;

	// Sphere 1 material
	color(&m_sphere1.color, 1.0f, 0.3f, 0.3f);
	m_sphere1.ambient = 0.1f; m_sphere1.diffuse = 0.7f;
	m_sphere1.specular = 0.3f; m_sphere1.shininess = 100;

	// Sphere 2 material
	color(&m_sphere2.color, 0.3f, 1.0f, 0.6f);
	m_sphere2.ambient = 0.1f; m_sphere2.diffuse = 0.7f;
	m_sphere2.specular = 0.1f; m_sphere2.shininess = 100;

	// Cylinder material
	color(&m_cylinder.color, 1.0f, 1.0f, 0.4f);
	m_cylinder.ambient = 0.1f; m_cylinder.diffuse = 0.7f;
	m_cylinder.specular = 0.3f; m_cylinder.shininess = 100;

	// Floor (XZ plane at Y = 0)
	floor.type = PLANE;
	floor.material = &m_wall;
	identity(&floor.transform);
	matrix_inverse(&floor.invs, &floor.transform);
	matrix_transpose(&floor.invs_trans, &floor.invs);

	// Back Wall (XY plane at Z = 3, facing -Z)
	translation(&trans, 0, 0, 3);
	rotate_x(&rot, M_PI_2);
	matrix_multiply(&tmp, &trans, &rot);
	back_wall.type = PLANE;
	back_wall.material = &m_wall;
	set_transform(&back_wall.transform, &tmp);
	matrix_inverse(&back_wall.invs, &back_wall.transform);
	matrix_transpose(&back_wall.invs_trans, &back_wall.invs);

	// Left Wall (YZ plane at X = -3, facing +X)
	translation(&trans, -3, 0, 0);
	rotate_z(&rot, -M_PI_2);
	matrix_multiply(&tmp, &trans, &rot);
	left_wall.type = PLANE;
	left_wall.material = &m_wall;
	set_transform(&left_wall.transform, &tmp);
	matrix_inverse(&left_wall.invs, &left_wall.transform);
	matrix_transpose(&left_wall.invs_trans, &left_wall.invs);

	// Sphere 1
	scaling(&scale, 0.5f, 0.5f, 0.5f);
	translation(&trans, -1.0f, 0.5f, 1.5f);
	matrix_multiply(&tmp, &trans, &scale);
	sphere1.type = SPHERE;
	sphere1.material = &m_sphere1;
	set_transform(&sphere1.transform, &tmp);
	matrix_inverse(&sphere1.invs, &sphere1.transform);
	matrix_transpose(&sphere1.invs_trans, &sphere1.invs);

	// Sphere 2
	scaling(&scale, 0.4f, 0.4f, 0.4f);
	translation(&trans, 1.0f, 0.4f, 2.5f);
	matrix_multiply(&tmp, &trans, &scale);
	sphere2.type = SPHERE;
	sphere2.material = &m_sphere2;
	set_transform(&sphere2.transform, &tmp);
	matrix_inverse(&sphere2.invs, &sphere2.transform);
	matrix_transpose(&sphere2.invs_trans, &sphere2.invs);

	// Cylinder
	scaling(&scale, 0.3f, 1.0f, 0.3f);
	translation(&trans, 0.0f, 1.0f, 2.0f);
	matrix_multiply(&tmp, &trans, &scale);
	cylinder.type = CYLINDER;
	cylinder.material = &m_cylinder;
	set_transform(&cylinder.transform, &tmp);
	matrix_inverse(&cylinder.invs, &cylinder.transform);
	matrix_transpose(&cylinder.invs_trans, &cylinder.invs);

	// Chain objects: floor -> back_wall -> left_wall -> sphere1 -> sphere2 -> cylinder
	floor.next = &back_wall;
	back_wall.next = &left_wall;
	left_wall.next = NULL;
	sphere1.next = &sphere2;
	sphere2.next = &cylinder;
	cylinder.next = NULL;
	world.components = &sphere1;

	// Light
	point(&world.light.position, -10.0f, 10.0f, -10.0f);
	color(&world.light.color, 1.0f, 1.0f, 1.0f);

	// Camera (top corner, looking into room)
	t_camera camera = camera_init(WIDTH, HEIGHT, M_PI / 3);
	t_tuple from, to, up;
	point(&from, 3.0f, 3.0f, -3.0f);   // Camera position
	point(&to, 0.0f, 1.0f, 2.0f);     // Look-at point
	vector(&up, 0.0f, 1.0f, 0.0f);
	view_transformation(&camera, &from, &to, &up);

	// Render
	static t_state state;
	state.mlx = mlx;
	state.img = img;
	state.camera = &camera;
	state.world = &world;
	state.tiles_x = (WIDTH + TILE_SIZE - 1) / TILE_SIZE;
	state.tiles_y = (HEIGHT + TILE_SIZE - 1) / TILE_SIZE;
	state.current_tile = 0;
	state.done = false;

	static t_mouse_state mouse_state;
	mouse_state.mlx = mlx,
	mouse_state.camera = &camera,
	mouse_state.world = &world;
	mouse_state.render_state = &state;
	mouse_state.is_dragging = false;
	mouse_state.last_x = 0;
	mouse_state.last_y = 0;
	mouse_state.selected_object = NULL;

	// Hook rendering into MLX loop
	mlx_mouse_hook(mlx, mouse_handler, &mouse_state);
	mlx_key_hook(mlx, key_handler, &mouse_state);
	mlx_loop_hook(mlx, render, &state);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}
