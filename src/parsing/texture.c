#include "cub3d.h"

bool	get_texture(char *file_str, t_cub3d *cub3d, char identifier, size_t *i)
{
	char	*texture;
	int		end_tex_name;

	// printf("file_str = %s \n", &file_str[*i]);
	skip_chars(file_str, i, " ");
	end_tex_name = *i;
	while (ft_isprint(file_str[end_tex_name]))
		end_tex_name++;
	texture = NULL;
	texture = ft_substr(&file_str[*i], 0, (end_tex_name - *i));
	// printf("texture = %s \n", texture);
	if (!texture)
		return (perror("substr fail\n"), false);
	if (!check_path(cub3d, identifier, texture))
		return (false);
	*i = end_tex_name;
	skip_chars(file_str, i, " ");
	if (file_str[*i] != '\n')
		return (perror("invalid map info\n"), false);
	return (true);
}

bool	check_path(t_cub3d *cub3d, char identifier, char *tex_path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(tex_path);
	if (!texture)
		return (perror("invalid path to texture\n"), free(tex_path), false);
	free(tex_path);
	if (identifier == 'N')
		cub3d->n_texture = texture;
	else if (identifier == 'E')
		cub3d->e_texture = texture;
	else if (identifier == 'S')
		cub3d->s_texture = texture;
	else if (identifier == 'W')
		cub3d->w_texture = texture;
	else
		return (false);
	return (true);
}