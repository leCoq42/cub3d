/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaan <mhaan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:20:30 by mhaan             #+#    #+#             */
/*   Updated: 2023/11/06 16:20:32 by mhaan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	get_color_header(char *file_str, t_cub3d *cub3d, char id, size_t *i)
{
	int32_t		r;
	int32_t		g;
	int32_t		b;

	r = get_r_g_b(file_str, i);
	if (r == -1)
		return (false);
	if (file_str[*i] != ',')
		return (false);
	g = get_r_g_b(file_str, i);
	if (g == -1)
		return (false);
	if (file_str[*i] != ',')
		return (false);
	b = get_r_g_b(file_str, i);
	if (b == -1)
		return (false);
	if (id == 'F')
		cub3d->f_col = combine_rgb(r, g, b);
	else if (id == 'C')
		cub3d->c_col = combine_rgb(r, g, b);
	return (true);
}

int	get_r_g_b(char *file_str, size_t *i)
{
	int	color;

	skip_chars(file_str, i, ", ");
	if (!ft_isdigit(file_str[*i]))
		return (-1);
	color = ft_atoi(&file_str[*i]);
	if (color < 0 || color > 255)
		return (-1);
	while (ft_isdigit(file_str[*i]))
		(*i)++;
	return (color);
}

uint32_t	combine_rgb(uint32_t r, uint32_t g, uint32_t b)
{
	return (r << 24 | g << 16 | b << 8 | 0XFF);
}
