/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:20:57 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:21:00 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_cub3d(t_cub3d *cub3d)
{
	if (cub3d->map_str)
		free(cub3d->map_str);
	if (cub3d->img)
		mlx_delete_image(cub3d->mlx, cub3d->img);
	clean_textures(cub3d);
	clean_char_arr(cub3d->char_arr);
	clean_int_arr(cub3d->int_arr, cub3d->map_height);
	if (cub3d->mlx)
		mlx_close_window(cub3d->mlx);
	if (cub3d->mlx)
		mlx_terminate(cub3d->mlx);
	free(cub3d);
}

void	clean_textures(t_cub3d *cub3d)
{
	if (cub3d->textures[0])
		mlx_delete_texture(cub3d->textures[0]);
	if (cub3d->textures[1])
		mlx_delete_texture(cub3d->textures[1]);
	if (cub3d->textures[2])
		mlx_delete_texture(cub3d->textures[2]);
	if (cub3d->textures[3])
		mlx_delete_texture(cub3d->textures[3]);
}

void	clean_char_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	clean_int_arr(int **arr, int h)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	if (!arr[0])
	{
		free(arr);
		return ;
	}
	while (i < h)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
