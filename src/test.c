#include "MLX42.h"
#include "cub3d.h"
#include <stdint.h>

int main(int argc, char **argv)
{
	(void)	argc;
	(void)	argv;
	t_cub3d	*cub3d;

	cub3d = init_cub3d();
	if (!cub3d)
		exit(1);
	cub3d_draw_image(cub3d, cub3d->mlx->width, cub3d->mlx->height);
	if (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0)
		exit(1);
	user_controls(cub3d);
	mlx_loop(cub3d->mlx);
	mlx_terminate(cub3d->mlx);
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

	ft_memset(img->pixels, bg_color, w * h * 4);

	//FLOOR CASTING
	// for(int y = 0; y < h; y++)
	for(int y = h / 2 + 1; y < h; ++y)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = player.x_dir - player.x_plane;
		float rayDirY0 = player.y_dir - player.y_plane;
		float rayDirX1 = player.x_dir + player.x_plane;
		float rayDirY1 = player.y_dir + player.y_plane;

		// Current y position compared to the center of the screen (the horizon)
		int p = y - h / 2;

		// Vertical position of the camera.
		float posZ = 0.5 * h;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / w;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / w;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = player.x_pos + rowDistance * rayDirX0;
		float floorY = player.y_pos + rowDistance * rayDirY0;

		for(int x = 0; x < w; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)(floorX);
			int cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
			int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			int floorTexture = 3;
			int ceilingTexture = 6;
			t_color color;

			// floor
			uint32_t tex_idx = (texWidth * ty + tx) * 4;
			uint32_t img_idx = (y * w + x) * 4;
			color.t_rgba.a = cub3d->textures[floorTexture]->pixels[tex_idx + 3];
			color.t_rgba.b = cub3d->textures[floorTexture]->pixels[tex_idx + 2];
			color.t_rgba.g = cub3d->textures[floorTexture]->pixels[tex_idx + 1];
			color.t_rgba.r = cub3d->textures[floorTexture]->pixels[tex_idx + 0];
			// color.c = (color.c >> 1) & 8355711; // make a bit darker
			cub3d->img->pixels[img_idx] = color.t_rgba.r;
			cub3d->img->pixels[img_idx + 1] = color.t_rgba.g;
			cub3d->img->pixels[img_idx + 2] = color.t_rgba.b;
			cub3d->img->pixels[img_idx + 3] = color.t_rgba.a;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			img_idx = ((h - y - 1) * w + x) * 4;
			color.t_rgba.a = cub3d->textures[ceilingTexture]->pixels[tex_idx + 3];
			color.t_rgba.b = cub3d->textures[ceilingTexture]->pixels[tex_idx + 2];
			color.t_rgba.g = cub3d->textures[ceilingTexture]->pixels[tex_idx + 1];
			color.t_rgba.r = cub3d->textures[ceilingTexture]->pixels[tex_idx + 0];
			// color.c = (color.c >> 1) & 8355711; // make a bit darker
			cub3d->img->pixels[img_idx] = color.t_rgba.r;
			cub3d->img->pixels[img_idx + 1] = color.t_rgba.g;
			cub3d->img->pixels[img_idx + 2] = color.t_rgba.b;
			cub3d->img->pixels[img_idx + 3] = color.t_rgba.a;
		}
	}

	//WALL CASTING
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
		double perpWallDist;
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

		//texturing calculations
		int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = player.y_pos + perpWallDist * rayDirY;
		else
			wallX = player.x_pos + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		//x coordinate on the texture
		int texX = (int)(wallX * (double)texWidth);
		if (side == 0 && rayDirX > 0)
			texX = texWidth - texX - 1;
		if (side == 1 && rayDirY < 0)
			texX = texWidth - texX - 1;

		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * texHeight / lineHeight;
		// Starting texture coordinate
		double texPos = ((double)drawStart - (double)h / 2 + (double)lineHeight / 2) * step;
		// double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			t_color color;
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (texHeight - 1);
			texPos += step;
			uint32_t tex_idx = (texWidth * texY + texX) * 4;
			uint32_t img_idx = (y * w + x) * 4;
			color.t_rgba.a = cub3d->textures[texNum]->pixels[tex_idx];
			color.t_rgba.b = cub3d->textures[texNum]->pixels[tex_idx + 1];
			color.t_rgba.g = cub3d->textures[texNum]->pixels[tex_idx + 2];
			color.t_rgba.r = cub3d->textures[texNum]->pixels[tex_idx + 3];
			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			// if (side == 1)
			// 	color.c = (color.c >> 1) & 8355711;
			cub3d->img->pixels[img_idx] = color.t_rgba.r;
			cub3d->img->pixels[img_idx + 1] = color.t_rgba.g;
			cub3d->img->pixels[img_idx + 2] = color.t_rgba.b;
			cub3d->img->pixels[img_idx + 3] = color.t_rgba.a;
		}
		//draw the pixels of the stripe as a vertical line
		draw_vert(cub3d, x, drawStart, drawEnd);
	}
}

