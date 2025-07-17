# ifndef FT_MINIRT_H
# define FT_MINIRT_H
# define _GNU_SOURCE

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


int ft_error(char *msg);
int values_validation(char *str);
void free_split(char **array);
bool	ft_isspace(char c);
float ft_atof(const char *str);
int set_world(char *line, t_world *world, int *index);
int set_light(char *line, t_world *world, int *index);
bool init_file_reader(char *filename, t_world *world);

# endif
