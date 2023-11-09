/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:20:25 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:20:28 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;

	if (argc != 2)
		exit(EXIT_FAILURE);
	cub3d = parse_file(argv[1]);
	if (!cub3d)
		exit(EXIT_FAILURE);
	if (!init_cub3d(cub3d))
		exit(EXIT_FAILURE);
	cub3d_draw_image(cub3d, SCREENWIDTH, SCREENHEIGHT);
	if (mlx_image_to_window(cub3d->mlx, cub3d->img, 0, 0) < 0)
	{
		clean_cub3d(cub3d);
		exit(EXIT_FAILURE);
	}
	cub3d_hooks(cub3d);
	mlx_loop(cub3d->mlx);
	clean_cub3d(cub3d);
	exit(EXIT_SUCCESS);
}
