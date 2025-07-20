/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:38:04 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/20 04:43:25 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

bool	line_break(char *line, int *index)
{
	int	i;

	i = *index;
	if (ft_strncmp(line, "\n", i) == 0)
		return (true);
	return (false);
}

bool	process_line(char *line, t_state *state)
{
	int	i;
	int	res;

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
		printf("calling plane processing function [%d]\n", i);
	else if (i != 0 && ft_strncmp(line, "cy", i) == 0)
		printf("calling cylinder processing function [%d]\n", i);
	else if (i != 0 && !line_break(line, &i))
		return (false);
	if (res)
		return (false);
	return (true);
}

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

bool	read_content(int fd, t_state *state)
{
	char	*line;

	line = NULL;
	while (true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!process_line(line, state))
		{
			free(line);
			return (false);
		}
		free(line);
		line = NULL;
	}
	return (true);
}

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
