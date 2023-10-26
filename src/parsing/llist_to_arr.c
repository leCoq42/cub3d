// #include "cub3d.h"

// // create_array(map); still needs to be implemented and free linked list afterwards
// void	llist_to_arr(t_map *map)
// {
// 	size_t y;
// 	t_node *curr;

// 	map->arr = ft_calloc(map->height, sizeof(char *));
// 	if (!map->arr)
// 		exit(0);
// 	y = 0;
// 	while (y < map->height)
// 	{
// 		map->arr[y] = ft_calloc(map->width, sizeof(char));
// 		if (!map->arr[y])
// 			exit(0); // should also free map here maybe
// 		y++;
// 	}
// 	curr = *map->llist;
// 	if (curr == NULL)
// 		exit(0);
// 	while (y < map->height && curr != NULL)
// 	{
// 		curr = fill_row(map->arr[y], curr, map);
// 	}
// }

// t_node *fill_row(char *row, t_node *curr, t_map *map)
// {
// 	size_t x;

// 	x = 0;
// 	while (x < map->width)
// 	{
// 		row[x] = curr->str[x];
// 		if (ft_isspace(row[x]))
// 			row[x] = 'x';
// 		x++;
// 	}
// 	return (curr->next);
// }

// int	ft_isspace(int c)
// {
// 	if ((c > 8 && c < 14) || c == 32)
// 		return (1);
// 	return (0);
// }