/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:20:36 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:20:37 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_dimensions(char **arr, t_cub3d *cub3d)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (arr[y] != NULL)
	{
		x = 0;
		while (arr[y][x] != '\0')
		{
			if (is_present("NESW", arr[y][x]))
			{
				cub3d->st_pos.x_pos = x;
				cub3d->st_pos.y_pos = y;
				cub3d->st_pos.dir = arr[y][x];
			}
			x++;
		}
		if (x > cub3d->map_width)
			cub3d->map_width = x;
		y++;
	}
	cub3d->map_height = y;
	if (cub3d->st_pos.dir != 0)
		return (true);
	return (false);
}

// void print_char_array(char **arr)
// {
// 	for (int i = 0; arr[i] != NULL; i++)
// 	{
// 		for (int j = 0; arr[i][j] != '\0'; j++)
// 		{
// 			// printf("(%d, %d) = %c", i, j, arr[i][j]);
// 			printf("%c", arr[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
// }

// void print_int_array(int **arr, size_t h, size_t w)
// {
// 	for (size_t i = 0; i < h; i++)
// 	{
// 		for (size_t j = 0; j < w; j++)
// 		{
// 			// printf("(%d, %d) = %c", i, j, arr[i][j]);
// 			printf("%d", arr[i][j]);
// 		}
// 		printf("\n");
// 	}
// 	printf("\n");
// }
