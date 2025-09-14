/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader1.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:38:04 by tsomacha          #+#    #+#             */
/*   Updated: 2025/08/02 15:06:18 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Returns true if the line should be treated as a blank/line-break entry.
 * Used to ignore lines that contain no meaningful tokens.
 */
bool	line_break(char *line, int *index)
{
	int	i;

	i = *index;
	if (ft_strncmp(line, "\n", i) == 0)
		return (true);
	return (false);
}

/**
 * Parses a single scene line and dispatches to the appropriate handler
 * (A, L, C, sp, pl, cy). Returns true on success, false on bad/unknown input.
 */
int	process_line(char *line, t_state *state)
{
	int	i;
	int	res;

	if (!line)
		return (0);
	if (ft_strncmp(line, "\n", ft_strlen(line)) == 0)
		return (1);
	i = 0;
	res = 0;
	while (line && line[i] && line[i] != ' ')
		i++;
	if (i != 0 && ft_strncmp(line, "A", i) == 0)
		res = set_world(line, state, &i);
	else if (i != 0 && ft_strncmp(line, "L", i) == 0)
		res = set_light(line, state, &i);
	else if (i != 0 && ft_strncmp(line, "C", i) == 0)
		res = set_camera(line, state, &i);
	else if (i != 0 && ft_strncmp(line, "sp", i) == 0)
		res = set_sphere(line, state, &i);
	else if (i != 0 && ft_strncmp(line, "pl", i) == 0)
		res = set_plane(line, state, &i);
	else if (i != 0 && ft_strncmp(line, "cy", i) == 0)
		res = set_cylinder(line, state, &i);
	return (res);
}

/**
 * Verifies the scene filename ends with the ".rt" extension.
 * Returns true if the extension is correct.
 */
bool	valid_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (ft_strncmp(&filename[len -3], ".rt", 3) != 0)
	{
		return (false);
	}
	return (true);
}

/**
 * Reads the entire file line by line, processing each with process_line().
 * Stops and returns false on the first parsing error;
 * true if all lines succeed.
 */
bool	read_content(int fd, t_state *state)
{
	char	*line;

	line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (false);
	while (line)
	{
		if (!extract_data(line, state))
		{
			free(line);
			line = get_next_line(fd);
			while (line)
			{
				free(line);
				line = get_next_line(fd);
			}
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}

/**
 * Validates the filename, opens the file, reads and parses its contents,
 * and reports clear errors for bad extension, open failure, or bad data.
 */
bool	init_file_reader(char *filename, t_state *state)
{
	int	fd;

	if (!valid_filename(filename))
	{
		ft_error("[ incorrect file extension ! ] \n");
		return (false);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error("[ failed to open the file ! ] \n");
		return (false);
	}
	if (!read_content(fd, state))
	{
		ft_error("[ incorrect data in the file ! ] \n");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}
