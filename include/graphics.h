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
	float half_width, half_height, pixel_size;
	t_mat transform;
	t_mat invs;
} t_camera;

void position(t_tuple *pp, t_ray *r, float t);
t_intersect	*cal_intersects(t_object *object, t_ray *rp, t_intersect *xs);
t_intersect	*intersections(t_intersect *xs, t_object *s, float value);
t_intersect	*hit(t_intersect *xs);

t_intersect	*intersections_sort(t_intersect *xs);
void free_intersections(t_intersect *xs);
void set_transform(t_mat *m1, t_mat *m2);
uint32_t tuple_to_color(t_tuple *tp);
t_intersect	*add_node(t_object *object, float t);

void normal_at(t_tuple *normal, t_object *s, t_tuple *world_point);
void reflect(t_tuple *out, t_tuple *in, t_tuple *normal);
void point_light(t_light *light, t_tuple *position, t_tuple *intensity);
void lighting(t_tuple *out, t_material *m, t_light *light, t_tuple *position, t_tuple *eye, t_tuple *normal);

t_intersect	*intersect_world(t_world *w, t_ray *r);
t_compute	prepare_compute(t_intersect *i, t_ray *r);
void shade_hit(t_tuple *colour, t_object *object, t_world *world, t_compute *comp);
t_tuple	color_at(t_world *world, t_ray *r);
void view_transformation(t_camera *camera, t_tuple *from, t_tuple *to, t_tuple *up);
t_camera *camera_init(int hsize, int vsize, float fov);
t_ray ray_for_pixel(t_camera *camera, int px, int py);
void render(mlx_image_t *img, t_camera *camera, t_world *world);
# endif
