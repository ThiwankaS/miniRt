# include "../../include/miniRt.h"

bool	ft_isspace(char c)
{
	if ( c == ' ' || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

float	get_interger_part(const char **str)
{
	float	result;

	result = 0.0;
	while (str && *str && **str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

float get_fractional_part(const char **str)
{
	float	fraction;
	float	divisor;

	fraction = 0.0;
	divisor = 10.0;
	while (str && *str && **str >= '0' && **str <= '9')
	{
		fraction += (**str - '0') / divisor;
		divisor *= 10.0;
		(*str)++;
	}
	return (fraction);
}

float ft_atof(const char *str)
{
	float	result;
	float	fraction;
	bool	is_negative;

	result = 0.0;
	fraction = 0.0;
	is_negative = false;
	while (str && *str && ft_isspace(*str))
		str++;
	if (str && *str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			is_negative = true;
		str++;
	}
	result = get_interger_part(&str);
	if (str && *str && *str == '.')
	{
		str++;
		fraction = get_fractional_part(&str);
	}
	result += fraction;
	if (is_negative)
		result = -result;
	return (result);
}
