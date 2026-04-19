#include "../../include/miniRt.h"

static t_tuple	camera_world_position(t_camera *camera)
{
	t_tuple	origin;

	point(&origin, 0.0f, 0.0f, 0.0f);
	return (matrix_multiply_by_tuple(&camera->invs, &origin));
}

static t_tuple	camera_world_direction(t_camera *camera, t_tuple *pos)
{
	t_tuple	look_at;
	t_tuple	dir;

	point(&look_at, 0.0f, 0.0f, -1.0f);
	look_at = matrix_multiply_by_tuple(&camera->invs, &look_at);
	dir = tuple_subtract(&look_at, pos);
	return (normalize(&dir));
}

int	interact_light(mlx_key_data_t key, t_state *state)
{
	t_light	*light;
	float	step;

	light = &state->world.light;
	if (!state->world.set_light)
	{
		printf(" ⛔ No light source in the scene.\n");
		return (FAILURE);
	}
	step = 1.0f;
	if (key.key == MLX_KEY_W)
		light->position.t[1] += step;
	else if (key.key == MLX_KEY_S)
		light->position.t[1] -= step;
	else if (key.key == MLX_KEY_A)
		light->position.t[0] -= step;
	else if (key.key == MLX_KEY_D)
		light->position.t[0] += step;
	else if (key.key == MLX_KEY_Z)
		light->position.t[2] += step;
	else if (key.key == MLX_KEY_X)
		light->position.t[2] -= step;
	else
		return (FAILURE);
	return (SUCCESS);
}

void	select_light_source(t_state *state)
{
	state->interact = LIGHT;
	printf("💡 Interactive mood for light ON.\n");
}

void	select_exit_interaction(t_state *state)
{
	state->interact = DEFAULT;
	state->selected_object = NULL;
	state->mode = DEFAULT;
	printf("👋 Interactive mood OFF.\n");
}

void	select_camera(t_state *state)
{
	state->interact = CAMERA;
	printf("📸 Interactive mood for camera ON.\n");
}

void	light_interact_mode(mlx_key_data_t keydata, t_state *state)
{
	if (interact_light(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (keydata.key == MLX_KEY_H && state->interact == LIGHT)
		help_light();
}

int	resize_sphere(mlx_key_data_t key, t_object *obj)
{
	float	step;

	step = 0.05f;
	if (!obj)
		return (FAILURE);
	if (key.key == MLX_KEY_UP)
		obj->radius = obj->radius + step;
	else if (key.key == MLX_KEY_DOWN)
		obj->radius = fmaxf(1.0f, obj->radius - step);
	else
		return (FAILURE);
	creating_sphere_object(obj);
	return (SUCCESS);
}

int	move_sphere(mlx_key_data_t key, t_object *obj)
{
	float	step;

	step = 0.1f;
	if (key.key == MLX_KEY_W)
		obj->y += step;
	else if (key.key == MLX_KEY_S)
		obj->y -= step;
	else if (key.key == MLX_KEY_A)
		obj->x -= step;
	else if (key.key == MLX_KEY_D)
		obj->x += step;
	else if (key.key == MLX_KEY_Z)
		obj->z += step;
	else if (key.key == MLX_KEY_X)
		obj->z -= step;
	else
		return (FAILURE);
	creating_sphere_object(obj);
	return (SUCCESS);
}

static void	sphere_interaction(mlx_key_data_t key, t_state *state)
{
	t_object	*selected;

	selected = state->selected_object;
	if (state->mode == DEFAULT || !selected)
		return ;
	if (state->mode == RESIZE && resize_sphere(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (state->mode == MOVE && move_sphere(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
}

void	sphere_interact_mode(mlx_key_data_t keydata, t_state *state)
{
	bool	left;
	bool	right;

	if (state->interact == DEFAULT)
		return ;
	left = mlx_is_key_down(state->mlx, MLX_KEY_LEFT_CONTROL);
	right = mlx_is_key_down(state->mlx, MLX_KEY_RIGHT_CONTROL);
	if (keydata.key == MLX_KEY_M && (left || right))
	{
		state->mode = MOVE;
		printf("you can move the selected sphere\n");
	}
	else if (keydata.key == MLX_KEY_R && (left || right))
	{
		state->mode = RESIZE;
		printf("you can resize the selected sphere\n");
	}
	else if (keydata.key == MLX_KEY_H)
		help_sphere();
	sphere_interaction(keydata, state);
}

int	resize_cylinder(mlx_key_data_t key, t_object *obj)
{
	if (!obj)
		return (FAILURE);
	if (key.key == MLX_KEY_UP)
		obj->radius += 0.1f;
	else if (key.key == MLX_KEY_DOWN)
		obj->radius = fmaxf(0.5f, obj->radius - 0.1f);
	else if (key.key == MLX_KEY_RIGHT)
		obj->height += 0.1f;
	else if (key.key == MLX_KEY_LEFT)
		obj->height = fmaxf(0.5f, obj->height - 0.1f);
	else
		return (FAILURE);
	printf("height : %.5f | radius : %.5f \n", obj->height, obj->radius);
	creating_cylinder_object(obj);
	return (SUCCESS);
}

int	move_cylinder(mlx_key_data_t key, t_object *obj)
{
	float	step;

	step = 0.1f;
	if (key.key == MLX_KEY_W)
		obj->y += step;
	else if (key.key == MLX_KEY_S)
		obj->y -= step;
	else if (key.key == MLX_KEY_A)
		obj->x -= step;
	else if (key.key == MLX_KEY_D)
		obj->x += step;
	else if (key.key == MLX_KEY_Z)
		obj->z += step;
	else if (key.key == MLX_KEY_X)
		obj->z -= step;
	else
		return (FAILURE);
	creating_cylinder_object(obj);
	return (SUCCESS);
}

int	rotate_cylinder(mlx_key_data_t key, t_object *obj)
{
	float	angle;
	t_mat	rotate;

	angle = 0.1f;
	if (key.key == MLX_KEY_W)
		rotate = rotate_y(angle);
	else if (key.key == MLX_KEY_S)
		rotate = rotate_y(-angle);
	else if (key.key == MLX_KEY_A)
		rotate = rotate_x(angle);
	else if (key.key == MLX_KEY_D)
		rotate = rotate_x(-angle);
	else if (key.key == MLX_KEY_Z)
		rotate = rotate_z(angle);
	else if (key.key == MLX_KEY_X)
		rotate = rotate_z(-angle);
	else
		return (FAILURE);
	obj->norm_v = matrix_multiply_by_tuple(&rotate, &obj->norm_v);
	obj->norm_v = normalize(&obj->norm_v);
	creating_cylinder_object(obj);
	return (SUCCESS);
}

static void	cylinder_interaction(mlx_key_data_t key, t_state *state)
{
	t_object	*selected;

	selected = state->selected_object;
	if (state->mode == DEFAULT || !selected)
		return ;
	if (state->mode == RESIZE && resize_cylinder(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (state->mode == MOVE && move_cylinder(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
	if (state->mode == ROTATE && rotate_cylinder(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
}

void	cylinder_interact_mode(mlx_key_data_t keydata, t_state *state)
{
	bool	left;
	bool	right;

	if (state->interact == DEFAULT)
		return ;
	left = mlx_is_key_down(state->mlx, MLX_KEY_LEFT_CONTROL);
	right = mlx_is_key_down(state->mlx, MLX_KEY_RIGHT_CONTROL);
	if (keydata.key == MLX_KEY_M && (left || right))
	{
		state->mode = MOVE;
		printf("you can move the selected cylinder\n");
	}
	else if (keydata.key == MLX_KEY_R && (left || right))
	{
		state->mode = RESIZE;
		printf("you can resize the selected cylinder\n");
	}
	else if (keydata.key == MLX_KEY_S && (left || right))
	{
		state->mode = ROTATE;
		printf("you can rotate the selected cylinder\n");
	}
	else if (keydata.key == MLX_KEY_H)
		help_cylinder();
	cylinder_interaction(keydata, state);
}

int	rotate_plane(mlx_key_data_t key, t_object *obj)
{
	float	angle;
	t_mat	rotate;

	angle = 0.1f;
	if (key.key == MLX_KEY_W)
		rotate = rotate_y(angle);
	else if (key.key == MLX_KEY_S)
		rotate = rotate_y(-angle);
	else if (key.key == MLX_KEY_A)
		rotate = rotate_x(angle);
	else if (key.key == MLX_KEY_D)
		rotate = rotate_x(-angle);
	else if (key.key == MLX_KEY_Z)
		rotate = rotate_z(angle);
	else if (key.key == MLX_KEY_X)
		rotate = rotate_z(-angle);
	else
		return (FAILURE);
	obj->norm_v = matrix_multiply_by_tuple(&rotate, &obj->norm_v);
	obj->norm_v = normalize(&obj->norm_v);
	creating_plane_object(obj);
	return (SUCCESS);
}

void	plane_interaction(mlx_key_data_t key, t_state *state)
{
	t_object	*selected;

	selected = state->selected_object;
	if (state->mode == DEFAULT || !selected)
		return ;
	if (state->mode == ROTATE && rotate_plane(key, selected) == SUCCESS)
	{
		render(state);
		printf("✅ update object !\n");
	}
}

void	plane_interact_mode(mlx_key_data_t keydata, t_state *state)
{
	bool	left;
	bool	right;

	if (state->interact == DEFAULT)
		return ;
	left = mlx_is_key_down(state->mlx, MLX_KEY_LEFT_CONTROL);
	right = mlx_is_key_down(state->mlx, MLX_KEY_RIGHT_CONTROL);
	if (keydata.key == MLX_KEY_M && (left || right))
	{
		state->mode = MOVE;
		printf("you can move the selected plane\n");
	}
	else if (keydata.key == MLX_KEY_S && (left || right))
	{
		state->mode = ROTATE;
		printf("you can rotate the selected plane\n");
	}
	else if (keydata.key == MLX_KEY_H)
		help_plane();
	plane_interaction(keydata, state);
}

int	rotate_camera(mlx_key_data_t key, t_state *state)
{
	t_tuple	pos;
	t_tuple	dir;
	t_mat	rotate;

	pos = camera_world_position(&state->camera);
	dir = camera_world_direction(&state->camera, &pos);
	if (key.key == MLX_KEY_W)
		rotate = rotate_y(0.1f);
	else if (key.key == MLX_KEY_S)
		rotate = rotate_y(-0.1f);
	else if (key.key == MLX_KEY_A)
		rotate = rotate_x(0.1f);
	else if (key.key == MLX_KEY_D)
		rotate = rotate_x(-0.1f);
	else if (key.key == MLX_KEY_Z)
		rotate = rotate_z(0.1f);
	else if (key.key == MLX_KEY_X)
		rotate = rotate_z(-0.1f);
	else
		return (FAILURE);
	dir = matrix_multiply_by_tuple(&rotate, &dir);
	dir = normalize(&dir);
	update_view(&state->camera, &pos, &dir);
	return (SUCCESS);
}

int	move_camera(mlx_key_data_t key, t_state *state)
{
	t_tuple	pos;
	t_tuple	dir;
	float	step;

	pos = camera_world_position(&state->camera);
	dir = camera_world_direction(&state->camera, &pos);
	step = 0.1f;
	if (key.key == MLX_KEY_W)
		pos.t[1] += step;
	else if (key.key == MLX_KEY_S)
		pos.t[1] -= step;
	else if (key.key == MLX_KEY_A)
		pos.t[0] -= step;
	else if (key.key == MLX_KEY_D)
		pos.t[0] += step;
	else if (key.key == MLX_KEY_Z)
		pos.t[2] += step;
	else if (key.key == MLX_KEY_X)
		pos.t[2] -= step;
	else
		return (FAILURE);
	update_view(&state->camera, &pos, &dir);
	return (SUCCESS);
}

int	zoom_camera(mlx_key_data_t key, t_state *state)
{
	float	step;

	step = 0.1f;
	if (key.key == MLX_KEY_A)
		state->camera.fov = fminf((float)M_PI, state->camera.fov + step);
	else if (key.key == MLX_KEY_D)
		state->camera.fov = fmaxf(0.1f, state->camera.fov - step);
	else
		return (FAILURE);
	update_fov(&state->camera, state->camera.fov);
	return (SUCCESS);
}

static void	camera_interaction(mlx_key_data_t keydata, t_state *state)
{
	if (state->mode == DEFAULT)
		return ;
	if (state->mode == ROTATE && rotate_camera(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update camera !\n");
	}
	if (state->mode == MOVE && move_camera(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update camera !\n");
	}
	if (state->mode == ZOOM && zoom_camera(keydata, state) == SUCCESS)
	{
		render(state);
		printf("✅ update camera !\n");
	}
}

void	camera_interaction_mode(mlx_key_data_t keydata, t_state *state)
{
	bool	left;
	bool	right;

	if (state->interact == DEFAULT && state->mode == DEFAULT)
		return ;
	left = mlx_is_key_down(state->mlx, MLX_KEY_LEFT_CONTROL);
	right = mlx_is_key_down(state->mlx, MLX_KEY_RIGHT_CONTROL);
	if (keydata.key == MLX_KEY_M && (left || right))
	{
		state->mode = MOVE;
		printf("you can move the camera\n");
	}
	else if (keydata.key == MLX_KEY_S && (left || right))
	{
		state->mode = ROTATE;
		printf("you can rotate the camera\n");
	}
	else if (keydata.key == MLX_KEY_F && (left || right))
	{
		state->mode = ZOOM;
		printf("you can zoom the camera\n");
	}
	else if (keydata.key == MLX_KEY_H)
		help_camera();
	camera_interaction(keydata, state);
}

void	select_mode(mlx_key_data_t keydata, t_state *state)
{
	t_object	*selected;

	(void)keydata;
	selected = state->selected_object;
	if (state->interact == LIGHT)
		light_interact_mode(keydata, state);
	if (state->interact == CAMERA)
		camera_interaction_mode(keydata, state);
	if (state->interact == OBJECT && selected)
	{
		if (selected->type == SPHERE)
			sphere_interact_mode(keydata, state);
		if (selected->type == CYLINDER)
			cylinder_interact_mode(keydata, state);
		if (selected->type == PLANE)
			plane_interact_mode(keydata, state);
	}
}

static const char	*object_type_name(int type)
{
	if (type == SPHERE)
		return ("sphere");
	if (type == CYLINDER)
		return ("cylinder");
	if (type == PLANE)
		return ("plane");
	return ("unknown");
}

void	select_next_object(t_state *state)
{
	static int	index = -1;
	t_object	*cur;
	int			i;

	i = 0;
	if (!state->world.components)
	{
		printf(" ⚠️  No objects in scene.\n");
		return ;
	}
	index = (index + 1) % state->world.obj_count;
	cur = state->world.components;
	while (cur && i++ < index)
		cur = cur->next;
	state->selected_object = cur;
	if (cur)
	{
		printf("🔄 Selected [%d]: object=%s radius=%.2f height=%.2f\n",
			index, object_type_name(cur->type), cur->radius, cur->height);
	}
	state->interact = OBJECT;
}
