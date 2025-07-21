/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 05:22:24 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/21 02:04:02 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define _GNU_SOURCE
# define WIDTH 1600
# define HEIGHT 1200
# define TILE_SIZE 64
# define SPHERE   1
# define PLANE    2
# define CYLINDER 3

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdint.h>
# include <fcntl.h>
# include <MLX42/MLX42.h>
# include "tuple.h"
# include "matrix.h"
# include "graphics.h"
# include "../ft_libft/libft.h"
# include "../ft_libft/ft_printf.h"
# include "../ft_libft/get_next_line.h"

int			ft_error(char *msg);
int			values_validation(char *str);
t_object	*init_object(void);
void		free_split(char **array);
void		clean_up(t_state *state);
void		add_object(t_state *state, t_object **s);
void		update_view(t_camera *camera, t_tuple *p, t_tuple *d);
bool		ft_isspace(char c);
float		ft_atof(const char *str);
int			set_world(char *line, t_state *state, int *index);
int			set_light(char *line, t_state *state, int *index);
int			set_camera(char *line, t_state *state, int *index);
int			set_sphere(char *line, t_state *state, int *index);
int			set_plane(char *line, t_state *state, int *index);
int			set_cylinder(char *line, t_state *state, int *index);
bool		init_file_reader(char *filename, t_state *state);

#endif
