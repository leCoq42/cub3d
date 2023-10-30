#include "cub3d.h"

void	show_fps(bool key_press)
{
	static int	second = 0;
	static int	frames = 0;
	static bool	on;

	if (key_press && !on)
		on = true;
	else if (key_press && on)
		on = false;
	else
		frames++;
	if (mlx_get_time() > second)
	{
		if (on)
			printf("FPS: %d\n", frames);
		second++;
		frames = 0;
	}
}
