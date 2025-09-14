/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsomacha <tsomacha@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 04:39:14 by tsomacha          #+#    #+#             */
/*   Updated: 2025/07/20 04:39:54 by tsomacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRt.h"

/**
 * Returns true if the character is ASCII whitespace (space or 9–13),
 * false otherwise.
 * Used by the float parser to skip leading whitespace safely.
 */
bool	ft_isspace(const char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (true);
	return (false);
}

/**
 * Parses the integer part of a decimal number from a C string pointer.
 * Advances the input pointer past consecutive digits
 * and returns the accumulated value.
 */
bool	get_interger_part(const char **str, float *result)
{
	int	count;

	count = 0;
	*result = 0.0;
	while (str && *str && **str >= '0' && **str <= '9')
	{
		*result = *result * 10.0 + (**str - '0');
		(*str)++;
		count++;
		if (count > 4)
			return (false);
	}
	if (*result > 4095.0f)
		return (false);
	return (true);
}

/**
 * Parses the fractional part after the decimal point from a C string pointer.
 * Accumulates digits with decreasing powers of ten,
 * advancing the pointer as it reads.
 */
bool	get_fractional_part(const char **str, float *fraction)
{
	float	divisor;
	int		count;

	*fraction = 0.0;
	divisor = 10.0;
	count = 0;
	if (str && *str && **str == '.')
		(*str)++;
	while (str && *str && **str >= '0' && **str <= '9' && count < 3)
	{
		*fraction = *fraction + (**str - '0') / divisor;
		divisor *= 10.0;
		(*str)++;
		count++;
	}
	return (true);
}

/**
 * Converts a decimal string to a float with optional leading whitespace
 * and sign.
 * Supports only integral and fractional parts (no exponent);
 * stops at the first non-digit.
 */
bool	ft_atof(const char *str, float *result)
{
	float	fraction;
	bool	is_negative;

	fraction = 0.0;
	is_negative = false;
	while (str && *str && ft_isspace(*str))
		str++;
	if (!str || *str == '\0')
		return (false);
	if (str && *str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			is_negative = true;
		str++;
	}
	if (!get_interger_part(&str, result))
		return (false);
	if (!get_fractional_part(&str, &fraction))
		return (false);
	*result += fraction;
	if (is_negative)
		*result = -(*result);
	return (true);
}
