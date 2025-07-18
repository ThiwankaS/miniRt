# include "../../include/miniRt.h"

int ft_error(char *msg)
{
	int len;

	write(2, "Error\n", 7);
	len = ft_strlen(msg);
	write(2, msg, len);
	return (len + 7);
}
