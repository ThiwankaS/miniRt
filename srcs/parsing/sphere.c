/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 06:35:49 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/20 11:45:50 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Creates a sphere object with given radius and position.
 * Applies scaling (radius) and translation (x, y, z) transformations,
 * then stores both the transformation matrix and its inverse/transpose
 * inside the object for later use in rendering (ray intersections).
 */
void	creating_sphere_object(t_object *s, float radius)
{
	t_mat	m1;
	t_mat	m2;

	m1 = scaling(radius, radius, radius);
	m2 = translation(s->x, s->y, s->z);
	s->transform = matrix_multiply(&m2, &m1);
	matrix_inverse(&s->invs, &s->transform);
	s->invs_trans = matrix_transpose(&s->invs);
}

/**
 * Parses and validates the radius value from a string.
 * Ensures the radius is non-negative and stores half the value
 * (since rendering logic use radius as diameter/2).
*/
bool	get_radius_s(char *line, float *v)
{
	float	d;

	if (!line)
		return (false);
	if (!ft_atof(line, &d))
		return (false);
	if (d < 0.0f)
		return (false);
	v[3] = d / 2.0f;
	return (true);
}

/**
 * Initializes and sets all required sphere attributes
 * (position, radius, color, material properties, transformations).
 * Links the sphere object into the world object list.
*/
void	set_sphere_values(t_state *state, t_object *s, float *v)
{
	if (!state || !s)
		return ;
	s->id = 1;
	s->type = SPHERE;
	s->x = v[0];
	s->y = v[1];
	s->z = v[2];
	s->radius = v[3];
	s->height = 0.0f;
	color(&s->color, v[4] / 255.0f, v[5] / 255.0f, v[6] / 255.0f);
	vector(&s->norm_v, 0.0f, 0.0f, 0.0f);
	s->ambient = &state->world.ambient;
	s->diffuse = &state->world.diffuse;
	s->specular = 0.01f;
	s->shininess = 50.0f;
	s->next = NULL;
	creating_sphere_object(s, v[3]);
	add_object(state, &s);
	state->world.obj_count++;
}

/**
 * Parses a sphere definition line, extracts its position, radius, and color,
 * then allocates and initializes a new sphere object in the scene.
 *
 * Expected format in `line`: "<pos> <radius> <color>"
 *   pos    = "x,y,z"
 *   radius = positive float
 *   color  = "R,G,B" (0-255 range)
*/
int	set_sphere(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[7];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 0);
	if (!extract_position(items[0], &v[0], &v[1], &v[2]))
		return (free_split(items), 0);
	if (!get_radius_s(items[1], v))
		return (free_split(items), 0);
	if (!extract_color(items[2], &v[4], &v[5], &v[6]))
		return (free_split(items), 0);
	s = init_object();
	set_sphere_values(state, s, v);
	free_split(items);
	return (1);
}
