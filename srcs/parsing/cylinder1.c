/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 02:25:04 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/27 07:37:51 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	get_position_cy(float *v, char *line);
bool	get_normal_cy(float *v, char *line);
bool	get_radius_cy(float *v, char *line);
bool	get_height_cy(float *v, char *line);
bool	get_color_cy(float *v, char *line);

void	set_cylinder_values(t_state *state, t_object *s, float *v)
{
	if (!state || !s)
		return ;
	s->id = 3;
	s->type = CYLINDER;
	s->x = v[0];
	s->y = v[1];
	s->z = v[2];
	vector(&s->norm_v, v[3], v[4], v[5]);
	s->radius = v[6];
	s->height = v[7];
	color(&s->color, v[8] / 255.0f, v[9] / 255.0f, v[10] / 255.0f);
	s->ambient = state->world.ambient;
	s->diffuse = state->world.diffuse;
	s->specular = 0.0f;
	s->shininess = 200.0f;
	s->transform = identity();
	s->invs = identity();
	s->invs_trans = identity();
	s->next = NULL;
	s->material = NULL;
	add_object(state, &s);
}

int	set_cylinder(char *line, t_state *state, int *index)
{
	char		**items;
	float		v[11];
	t_object	*s;

	items = ft_split(&line[*index], ' ');
	if (!items)
		return (free_split(items), 1);
	if (!get_position_cy(v, items[0]))
		return (free_split(items), 1);
	if (!get_normal_cy(v, items[1]))
		return (free_split(items), 1);
	if (!get_radius_cy(v, items[2]))
		return (free_split(items), 1);
	if (!get_height_cy(v, items[3]))
		return (free_split(items), 1);
	if (!get_color_cy(v, items[4]))
		return (free_split(items), 1);
	s = init_object();
	set_cylinder_values(state, s, v);
	free_split(items);
	return (0);
}
