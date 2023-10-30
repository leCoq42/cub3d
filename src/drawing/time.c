#include "cub3d.h"

void	show_fps(t_cub3d *cub3d, bool key_press)
{
	static int	second = 0;
	static int	frames = 0;
	static bool	on;

	(void)cub3d;
	if (key_press && !on)
		on = true;
	else if (key_press && on)
		on = false;
	else
		frames++;
	if (mlx_get_time() > second)
	{
		if (on)
		{
			// mlx_put_string(cub3d->mlx, "FPS:", 10, 10);
			// mlx_put_string(cub3d->mlx, ft_itoa(frames), 50, 10);
			ft_printf("FPS: %d\n", frames);
		}
		second++;
		frames = 0;
	}
}
