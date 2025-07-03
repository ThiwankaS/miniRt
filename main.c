# include "include/miniRt.h"

int main(void)
{
	const char *msg = "Hello, world!";
	printf("%s length is %zu\n", msg, ft_strlen(msg));

	mlx_t *mlx = mlx_init(200, 200, "miniRt demo", false);
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
	return (0);
}
