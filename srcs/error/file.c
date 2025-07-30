/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 08:53:36 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/30 08:54:21 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

int	ft_error(char *msg)
{
	int	len;

	write(2, "Error\n", 7);
	len = ft_strlen(msg);
	write(2, msg, len);
	return (len + 7);
}
