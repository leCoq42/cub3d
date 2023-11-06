#include "cub3d.h"
#include "MLX42.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
		exit(0);
	cub3d = parse_file(argv[1]);
	if (!cub3d)
		exit(EXIT_FAILURE);
	if (!init_cub3d(cub3d))
		exit(EXIT_FAILURE);
	cub3d_draw_image(cub3d, screenWidth, screenHeight);
	if (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0)
		exit(EXIT_FAILURE);
	user_controls(cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
	exit(EXIT_SUCCESS);
}
