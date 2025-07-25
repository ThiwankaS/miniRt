#include "../../include/miniRt.h"

t_compute	prepare_compute(float t, t_object *object, t_ray *r)
{
	t_compute comp;
	float dot_val;

	comp.value = t;
	comp.object = object;
	position(&comp.p, r, t);
	tuple_negate(&comp.eye_v, &r->direction);
	comp.normal_v = normal_at(object, &comp.p);
	dot_val = dot(&comp.eye_v, &comp.normal_v);
	if (dot_val < 0.0f)
	{
		comp.inside = true;
		tuple_negate(&comp.normal_v, &comp.normal_v);
	}
	else
	{
		comp.inside = false;
	}
	return comp;
}

t_tuple	color_at(t_world *world, t_ray *r)
{
	t_tuple		colour;
	t_compute	comp;
	t_hit h;

	h = find_hit(world, r);
	color(&colour, 0.3f, 0.3f, 0.3f);
	if (h.hit)
	{
		comp = prepare_compute(h.t, h.object, r);
		colour = lighting(h.object, &world->light, &comp);
		return (colour);
	}
	return (colour);
}

void view_transformation(t_camera *camera, t_tuple *from, t_tuple *to, t_tuple *up)
{
	t_tuple sub;
	t_tuple forward;
	t_tuple left;
	t_tuple true_up;
	t_mat orientation;
	t_mat translate;

	tuple_subtract(&sub, to, from);
	normalize(&forward, &sub);
	cross(&left, &forward, up);
	normalize(&left, &left);
	cross(&true_up, &left, &forward);
	normalize(&true_up, &true_up);
	identity(&orientation);
	orientation.m[0][0] = left.t[0];
	orientation.m[0][1] = left.t[1];
	orientation.m[0][2] = left.t[2];
	orientation.m[1][0] = true_up.t[0];
	orientation.m[1][1] = true_up.t[1];
	orientation.m[1][2] = true_up.t[2];
	orientation.m[2][0] = -forward.t[0];
	orientation.m[2][1] = -forward.t[1];
	orientation.m[2][2] = -forward.t[2];
	orientation.m[3][3] = 1;
	translation(&translate, -from->t[0], -from->t[1], -from->t[2]);
	matrix_multiply(&camera->transform, &orientation, &translate);
	matrix_inverse(&camera->invs, &camera->transform);
}

t_ray ray_for_pixel(t_camera *camera, int px, int py)
{
	float		xoffset;
	float		yoffset;
	float		world_x;
	float		world_y;
	t_tuple		p;
	t_tuple		abs_p;
	t_tuple		pixel;
	t_tuple		origin;
	t_tuple		temp;
	t_tuple		direction;
	t_ray		r;

	xoffset = (px + 0.5f) * camera->pixel_size;
	yoffset = (py + 0.5f) * camera->pixel_size;
	world_x = camera->half_width - xoffset;
	world_y = camera->half_height - yoffset;

	point(&p, world_x, world_y, -1.0f);      // Camera space
	point(&abs_p, 0.0f, 0.0f, 0.0f);         // Camera origin

	// Transform both to world space
	matrix_multiply_by_tuple(&pixel, &camera->invs, &p);
	matrix_multiply_by_tuple(&origin, &camera->invs, &abs_p);
	tuple_subtract(&temp, &pixel, &origin); // Direction = pixel - origin
	normalize(&direction, &temp);
	point(&r.origin, origin.t[0], origin.t[1], origin.t[2]);
	vector(&r.direction, direction.t[0], direction.t[1], direction.t[2]);
	return (r);
}

// void render(void *param)
// {
// 	t_state *s = (t_state *)param;

// 	if (s->done)
// 		return;

// 	int tile_index = s->current_tile;
// 	if (tile_index >= s->tiles_x * s->tiles_y)
// 	{
// 		mlx_image_to_window(s->mlx, s->img, 0, 0);
// 		s->done = true;
// 		return;
// 	}
// 	int tile_x = (tile_index % s->tiles_x) * TILE_SIZE;
// 	int tile_y = (tile_index / s->tiles_x) * TILE_SIZE;
// 	int max_x = tile_x + TILE_SIZE;
// 	int max_y = tile_y + TILE_SIZE;

// 	if (max_x > s->camera.hsize)
// 		max_x = s->camera.hsize;
// 	if (max_y > s->camera.vsize)
// 		max_y = s->camera.vsize;

// 	int y = tile_y;
// 	while (y < max_y)
// 	{
// 		int x = tile_x;
// 		while (x < max_x)
// 		{
// 			t_ray r = ray_for_pixel(&s->camera, x, y);
// 			t_tuple c = color_at(&s->world, &r);
// 			mlx_put_pixel(s->img, x, y, tuple_to_color(&c));
// 			x++;
// 		}
// 		y++;
// 	}
// 	s->current_tile++;
// }

t_object *pick_object_at(int px, int py, t_camera *camera, t_world *world)
{
	t_ray ray = ray_for_pixel(camera, px, py);
	t_hit hit = find_hit(world, &ray);
	if (hit.hit)
		return hit.object;
	return NULL;
}

void handle_drag(void *param)
{
	t_mouse_state *ms = (t_mouse_state *)param;
	int x, y;

	if (!ms->is_dragging || !ms->selected_object)
		return;

	mlx_get_mouse_pos(ms->mlx, &x, &y);
	int dx = x - ms->last_x;
	int dy = y - ms->last_y;

	if (dx != 0 || dy != 0)
	{
		// Convert to world space delta — tweak this factor as needed
		float move_x = dx * 0.01f;
		float move_y = -dy * 0.01f;

		// Move the object in X and Y direction
		t_mat translate, result;
		translation(&translate, move_x, move_y, 0.0f);
		matrix_multiply(&result, &translate, &ms->selected_object->transform);
		set_transform(&ms->selected_object->transform, &result);
		matrix_inverse(&ms->selected_object->invs, &ms->selected_object->transform);

		// Reset renderer
		ms->render_state->current_tile = 0;
		ms->render_state->done = false;
		ms->last_x = x;
		ms->last_y = y;
	}
}

void mouse_handler(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_mouse_state *ms = (t_mouse_state *)param;

	int x, y;
	mlx_get_mouse_pos(ms->mlx, &x, &y);
	(void)mods;
	if (button == MLX_MOUSE_BUTTON_LEFT)
	{
		if (action == MLX_PRESS)
		{
			ms->last_x = x;
			ms->last_y = y;
			ms->selected_object = pick_object_at(x, y, ms->camera, ms->world);
			ms->is_dragging = (ms->selected_object != NULL);
		}
		else if (action == MLX_RELEASE)
		{
			ms->is_dragging = false;
			ms->selected_object = NULL;
		}
	}
}

void key_handler(mlx_key_data_t keydata, void *param)
{
	t_mouse_state *ms = (t_mouse_state *)param;
	t_object *obj = ms->selected_object;
	t_mat m, result;

	if (!obj || !keydata.key || keydata.action != MLX_PRESS)
		return;

	// Movement
	if (keydata.key == MLX_KEY_W)
		translation(&m, 0, 0.1f, 0);
	else if (keydata.key == MLX_KEY_S)
		translation(&m, 0, -0.1f, 0);
	else if (keydata.key == MLX_KEY_A)
		translation(&m, -0.1f, 0, 0);
	else if (keydata.key == MLX_KEY_D)
		translation(&m, 0.1f, 0, 0);
	else if (keydata.key == MLX_KEY_Q)
		translation(&m, 0, 0, -0.1f);
	else if (keydata.key == MLX_KEY_E)
		translation(&m, 0, 0, 0.1f);

	// Scaling
	else if (keydata.key == MLX_KEY_Z)
		scaling(&m, 0.9f, 0.9f, 0.9f);
	else if (keydata.key == MLX_KEY_X)
		scaling(&m, 1.1f, 1.1f, 1.1f);

	// Rotation (Y-axis)
	else if (keydata.key == MLX_KEY_R)
		rotate_y(&m, 0.1f);
	else if (keydata.key == MLX_KEY_T)
		rotate_y(&m, -0.1f);

	// Deselect
	else if (keydata.key == MLX_KEY_ESCAPE)
	{
		ms->selected_object = NULL;
		ms->is_dragging = false;
		return;
	}
	else
		return;

	// Apply transformation
	matrix_multiply(&result, &m, &obj->transform);
	set_transform(&obj->transform, &result);
	matrix_inverse(&obj->invs, &obj->transform);

	// Trigger rerender
	ms->render_state->current_tile = 0;
	ms->render_state->done = false;
}
