# ifndef FT_GRAPHICS_H
# define FT_GRAPHICS_H

# include "miniRt.h"

typedef struct s_material
{
	float ambient;
	float diffuse;
	float specular;
	float shininess;
	t_tuple color;
} t_material;

typedef struct s_light
{
	t_tuple color;
	t_tuple position;
} t_light;

typedef struct s_object
{
	int   id;
	float x;
	float y;
	float z;
	float type;
	float radius;
	t_mat transform;
	t_mat invs;
	t_material *material;
	struct s_object *next;
} t_object;

typedef struct s_intersect
{
	int count;
	float value;
	t_object *object;
	struct s_intersect *next;
} t_intersect;

typedef struct s_world
{
	t_light light;
	t_object *components;
} t_world;

typedef struct s_compute
{
	bool inside;
	float value;
	t_object *object;
	t_tuple p;
	t_tuple eye_v;
	t_tuple normal_v;
} t_compute;

typedef struct s_camera
{
	int hsize;
	int vsize;
	float fov;
	float half_width;
	float half_height;
	float pixel_size;
	t_mat transform;
	t_mat invs;
} t_camera;

typedef struct s_hit
{
	float		t;
	t_object	*object;
	bool		hit;
} t_hit;

typedef struct s_tile_state {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_camera	*camera;
	t_world		*world;
	int			tiles_x;
	int			tiles_y;
	int			current_tile;
	bool		done;
}	t_tile_state;

typedef struct s_mouse_state {
	mlx_t		*mlx;
	t_camera	*camera;
	t_world		*world;
	t_tile_state *render_state;
	bool		is_dragging;
	int			last_x;
	int			last_y;
	t_object	*selected_object;
}	t_mouse_state;

void position(t_tuple *pp, t_ray *r, float t);
t_hit	find_hit(t_world *world, t_ray *ray);

void set_transform(t_mat *m1, t_mat *m2);
uint32_t tuple_to_color(t_tuple *tp);

void normal_at(t_tuple *normal, t_object *s, t_tuple *world_point);
void reflect(t_tuple *out, t_tuple *in, t_tuple *normal);
void point_light(t_light *light, t_tuple *position, t_tuple *intensity);
void lighting(t_tuple *out, t_material *m, t_light *light, t_tuple *position, t_tuple *eye, t_tuple *normal);

t_compute	prepare_compute(float t, t_object *object, t_ray *r);
void shade_hit(t_tuple *colour, t_object *object, t_world *world, t_compute *comp);
t_tuple	color_at(t_world *world, t_ray *r);
void view_transformation(t_camera *camera, t_tuple *from, t_tuple *to, t_tuple *up);
t_camera camera_init(int hsize, int vsize, float fov);
t_ray ray_for_pixel(t_camera *camera, int px, int py);
void render(void *param);

void handle_drag(void *param);
t_object *pick_object_at(int px, int py, t_camera *camera, t_world *world);
void key_handler(mlx_key_data_t keydata, void *param);
void mouse_handler(mouse_key_t button, action_t action, modifier_key_t mods, void *param);
# endif
