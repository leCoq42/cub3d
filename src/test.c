#include "MLX42.h"
#include "cub3d.h"

int main(int argc, char **argv)
{
	(void)argc, (void)argv;
	t_cub3d	*cub3d;

	cub3d = init_cub3d();
	if (!cub3d)
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


void	cub3d_draw_image(t_cub3d *cub3d, int32_t w, int32_t h)
{
	t_player	player;
	mlx_image_t	*img;
	int32_t		bg_color;

	player = cub3d->player;
	img = cub3d->img;
	bg_color = cub3d->bg_color;

	ft_memset(img->pixels, bg_color, screenHeight * screenWidth * sizeof(int32_t));
	for(int x = 0; x < w; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		double rayDirX = player.x_dir + player.x_plane * cameraX;
		double rayDirY = player.y_dir + player.y_plane * cameraX;

		//which box of the map we're in
		int mapX = (int)player.x_pos;
		int mapY = (int)player.y_pos;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		//which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		//where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		//unlike (dirX, dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player.x_pos - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player.x_pos) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player.y_pos - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player.y_pos) * deltaDistY;
		}

		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[mapX][mapY] > 0)
				hit = 1;
		}

		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
		int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		t_point p1 = init_point(x, drawStart, 0, 0x00000000);
		t_point p2 = init_point(x, drawEnd, 0, 0x00000000);

		//choose wall color
		uint32_t color;
		switch(worldMap[mapX][mapY])
		{
			case 1:  color = 0xFF0000FF;  break; //red
			case 2:  color = 0x00FF00FF;  break; //green
			case 3:  color = 0x0000FFFF;  break; //blue
			case 4:  color = 0xFFFFFFFF;  break; //white
			default: color = 0x00FFFFFF;  break; //yellow
		}

		//give x and y sides different brightness
		if(side == 1)
			color = color / 2;

		p1.c.c = color;
		p2.c.c = color;

		//draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		draw_line(cub3d, p1, p2);
	}
}

void	draw_line(t_cub3d *cub3d, t_point p1, t_point p2)
{
	if (cub3d->wu)
		wu_line(cub3d, p1, p2);
	else
		bresenham_line(cub3d, p1, p2);
}
