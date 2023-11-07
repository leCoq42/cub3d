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
	clean_textures(cub3d);
	clean_char_arr(cub3d->char_arr);
	clean_int_arr(cub3d->int_arr, cub3d->map_height);
	free(cub3d);
}

void	clean_textures(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 4 && cub3d->textures[i] != NULL)
	{
		free(cub3d->textures[i]);
		i++;
	}
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
