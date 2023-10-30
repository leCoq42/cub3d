#include "cub3d.h"
#include "MLX42.h"

// int	main(int argc, char **argv)
// {
// 	t_cub3d	*cub3d;

// 	if (argc != 2)
// 		exit(0);
// 	cub3d = parse_file(argv[1]);
// 	// mlx_start(map);
// 	// clean_up_arr(map->points, map);
// 	free(cub3d);
// 	return (0);
// }

int main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
		exit(0);
	cub3d = parse_file(argv[1]);
	if (!cub3d)
		exit(1);
	if (!init_cub3d(cub3d))
		exit(1);
	cub3d_draw_image(cub3d, cub3d->mlx->width, cub3d->mlx->height);
	if (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0)
		exit(1);
	user_controls(cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
	exit(EXIT_SUCCESS);
}

// int main(int argc, char **argv)
// {
// 	(void)	argc;
// 	(void)	argv;
// 	t_cub3d	*cub3d;

// 	cub3d = init_cub3d();
// 	if (!cub3d)
// 		exit(1);
// 	cub3d_draw_image(cub3d, cub3d->mlx->width, cub3d->mlx->height);
// 	if (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0)
// 		exit(1);
// 	user_controls(cub3d);
// 	mlx_loop(cub3d->mlx);
// 	mlx_terminate(cub3d->mlx);
// 	exit(EXIT_SUCCESS);
// }
