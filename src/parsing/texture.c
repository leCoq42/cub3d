/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:20:51 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:20:54 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_texture(char *file_str, t_cub3d *cub3d, char identifier, size_t *i)
{
	char	*tex_path;
	int		end_tex_name;

	skip_chars(file_str, i, " ");
	end_tex_name = *i;
	while (!ft_isspace(file_str[end_tex_name]))
		end_tex_name++;
	tex_path = NULL;
	tex_path = ft_substr(&file_str[*i], 0, (end_tex_name - *i));
	if (!tex_path)
		return (perror("Error\nsubstr fail"), false);
	if (!check_path(cub3d, identifier, tex_path))
		return (false);
	*i = end_tex_name;
	skip_chars(file_str, i, " ");
	if (file_str[*i] != '\n')
		return (perror("Eror\ninvalid map info"), false);
	return (true);
}

bool	check_path(t_cub3d *cub3d, char identifier, char *tex_path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(tex_path);
	free(tex_path);
	if (!texture)
		return (perror("Error\ninvalid path to texture"), false);
	if (identifier == 'N')
		cub3d->textures[0] = texture;
	else if (identifier == 'E')
		cub3d->textures[1] = texture;
	else if (identifier == 'S')
		cub3d->textures[2] = texture;
	else if (identifier == 'W')
		cub3d->textures[3] = texture;
	else
		return (mlx_delete_texture(texture), false);
	return (true);
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\0');
}
