# include "include/miniRt.h"

int main(void)
{
	ft_printf("hey, bro !\n");

	double result = M_PI / 2;
	printf("result : %.5f\n", result);

	char *line = NULL;
	int fd = open("test.txt", R_OK, 0644);
	if(fd < 0)
		return 0;
	line = get_next_line(fd);
	while(line != NULL)
	{
		ft_printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
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
