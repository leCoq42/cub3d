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
	cub3d_draw_image(cub3d, screenWidth, screenHeight);
	if (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0)
		exit(1);

	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame
	// screen(screenWidth, screenHeight, 0, "Raycaster");
	//timing for input and FPS counter
	// oldTime = time;
	// time = getTicks();
	// double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	// printf("%f\n", 1.0 / frameTime); //FPS counter
	// redraw();
	// cls();

	//speed modifiers
	// double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
	// double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	// readKeys();
	//
	user_controls(cub3d);
	mlx_loop(cub3d->mlx);
	exit(EXIT_SUCCESS);
}
