// #include "cub3d.h"

// char *read_fd(int fd)
// {
// 	char *buffer = NULL;
// 	size_t buffer_size = 0;
// 	size_t total_bytes_read = 0;

// 	while (1) 
// 	{
// 		// Resize the buffer to accommodate more data
// 		buffer = (char *)realloc(buffer, total_bytes_read + buffer_size + 1);
// 		if (buffer == NULL) {
// 			fprintf(stderr, "Memory allocation error.\n");
// 			exit(EXIT_FAILURE);
// 		}
// 		// Read data into the buffer
// 		size_t bytes_read = fread(buffer + total_bytes_read, 1, buffer_size, stdin);
// 		total_bytes_read += bytes_read;
// 		// Check for end of file or read error
// 		if (bytes_read < buffer_size) {
// 			if (feof(stdin)) {
// 				break;  // End of file
// 			} else {
// 				perror("Error reading file");
// 				free(buffer);
// 				exit(EXIT_FAILURE);
// 			}
// 		}
// 	}
// 	// Null-terminate the string
// 	buffer[total_bytes_read] = '\0';
// 	return buffer;
// }

// void	file_to_str(int fd, t_map *map)
// {
// 	map->file_str = read_fd(fd);
	
// }


// void	file_to_llist(int fd, t_map *map)
// {
// 	char	*line;
// 	t_node	*prev_node;

// 	line = get_next_line(fd);
// 	if (!line)
// 		exit(0);
// 	map->llist = ft_calloc(1, sizeof(t_node *));
// 	if (!map->llist)
// 		exit(0);
// 	map->height = 0;
// 	prev_node = NULL;
// 	while (line != NULL)
// 	{
// 		map->width = (ft_strlen(line) > map->width) ? ft_strlen(line) : map->width;
// 		prev_node = add_node(line, map, prev_node);
// 		free(line);
// 		line = get_next_line(fd);
// 		map->height++;
// 	}
// 	// check_values(prev_node->str, "1");
// }

// t_node	*add_node(char *line, t_map *map, t_node *prev_node)
// {
// 	t_node	*new_node;

// 	// if (prev_node == NULL)
// 	// 	check_values(line, "1")
// 	// else
// 	// 	check_values(line, map->allowed_values)
// 	new_node = ft_calloc(1, sizeof(t_node));
// 	if (!new_node)
// 		exit(0);
// 	new_node->str = line;
// 	prev_node = list_add_back(map->llist, new_node, prev_node);
// 	return (prev_node);
// }

// t_node	*list_add_back(t_node **llist, t_node *new_node, t_node *prev_node)
// {
// 	if (!*llist)
// 		*llist = new_node;
// 	if (!llist || !new_node)
// 		return (NULL);
// 	if (prev_node != NULL)
// 		prev_node->next = new_node;
// 	return (new_node);
// }