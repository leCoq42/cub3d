/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbrouwer <vbrouwer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:20:46 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 17:02:56 by vbrouwer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub3d	*parse_file(char *filename)
{
	int		fd;
	t_cub3d	*cub3d;

	fd = check_filename(filename);
	if (fd < 0)
		return (perror("Error\ninvalid file"), NULL);
	cub3d = ft_calloc(1, sizeof(t_cub3d));
	if (!cub3d)
		return (perror("Error\nmalloc fail"), NULL);
	if (!parse_header(fd, cub3d))
		return (clean_cub3d(cub3d), NULL);
	if (!parse_map(cub3d))
		return (clean_cub3d(cub3d), NULL);
	return (cub3d);
}
