/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 11:39:48 by aoshinth          #+#    #+#             */
/*   Updated: 2025/08/03 06:13:39 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "miniRt.h"

typedef struct s_light
{
	t_tuple	color;
	t_tuple	position;
}	t_light;

typedef struct s_object
{
	int				id;
	int				type;
	float			x;
	float			y;
	float			z;
	float			radius;
	float			height;
	float			*ambient;
	float			*diffuse;
	float			specular;
	float			shininess;
	t_tuple			color;
	t_tuple			norm_v;
	t_mat			transform;
	t_mat			invs;
	t_mat			invs_trans;
	struct s_object	*next;
}	t_object;

typedef struct s_world
{
	bool		set_ambient;
	bool		set_light;
	float		ambient;
	float		diffuse;
	t_tuple		colour;
	t_light		light;
	t_object	*components;
	int			obj_count;
}	t_world;

typedef struct s_compute
{
	bool		inside;
	bool		shadowed;
	float		value;
	t_object	*object;
	t_tuple		p;
	t_tuple		over_p;
	t_tuple		eye_v;
	t_tuple		normal_v;
}	t_compute;

typedef struct s_camera
{
	int		hsize;
	int		vsize;
	float	fov;
	float	half_width;
	float	half_height;
	float	pixel_size;
	bool	set_camera;
	t_mat	transform;
	t_mat	invs;
}	t_camera;

typedef struct s_hit
{
	float		t;
	t_object	*object;
	bool		hit;
}	t_hit;

typedef struct s_state
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_camera	camera;
	t_world		world;
	int			width;
	int			height;
	t_object	*selected_object;
	int			interact;
	int			mode;
	bool		done;
}	t_state;

void		position(t_tuple *pp, t_ray *r, float t);
t_hit		find_hit(t_world *world, t_ray *ray);
void		creating_plane_object(t_object *s);
void		creating_sphere_object(t_object *s);
void		creating_cylinder_object(t_object *s);
void		find_hit_cylinder(t_object *object, t_ray *r, t_hit *h);
void		hit_cap(t_object *object, t_ray *r, t_hit *h);
void		find_hit_plane(t_object *object, t_ray *r, t_hit *h);
void		find_hit_sphere(t_object *object, t_ray *r, t_hit *h);
void		set_transform(t_mat *m1, t_mat *m2);
uint32_t	tuple_to_color(t_tuple *tp);
t_tuple		normal_at(t_object *s, t_tuple *world_point);
t_tuple		reflect(t_tuple *in, t_tuple *normal);
t_tuple		lighting(t_object *obj, t_light *light, t_compute *comp);
t_compute	prepare_compute(float t, t_object *object, t_ray *r,
				t_world *world);
t_tuple		color_at(t_world *world, t_ray *r);
void		view_trans(t_camera *camera, t_tuple *from, t_tuple *to,
				t_tuple *up);
t_ray		ray_for_pixel(t_camera *camera, int px, int py);
void		update_fov(t_camera *camera, float fov);
void		render_if_resized(void *param);
void		render(t_state *state);
void		keypress(mlx_key_data_t keydata, void *param);
int			change_value(mlx_key_data_t keydata, t_state *state);
int			resize_sphere(mlx_key_data_t key, t_object *obj);
int			move_sphere(mlx_key_data_t key, t_object *obj);
int			resize_cylinder(mlx_key_data_t key, t_object *obj);
void		handle_resize(t_state *state, int32_t cur_w, int32_t cur_h);
void		select_next_object(t_state *state);
int			interact_light(mlx_key_data_t key, t_state *state);

void	select_ligth_source(t_state *state);
void	select_exit_interaction(t_state *state);
void	select_camera(t_state *state);
void	select_mode(mlx_key_data_t keydata, t_state *state);
void	help_menu(void);
void	help_mode(void);
void	help_light(void);
void	help_sphere(void);
void	cylinder_interact_mode(mlx_key_data_t keydata, t_state *state);
#endif
