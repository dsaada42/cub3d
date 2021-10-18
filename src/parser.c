/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:54:58 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/18 21:25:36 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_params(t_vars *v)
{
	if (v->floor && v->ceiling && v->north && v->south && v->east && v->west)
		return (1);
	else
		return (0);
}

int	parser(int fd, t_vars *v)
{	
	char	*buffer;
	int	check;

	v->north = 0;
        v->south = 0;
        v->west = 0;
        v->east = 0;
        v->sprite = 0;
        v->floor = 0;
        v->ceiling = 0;
	check = 0;
	while (check == 0 && get_next_line(fd, &buffer))
	{
		if (buffer[0] == 'N' && buffer[1] == 'O')
			parse_north_path(v, buffer);
		else if (buffer[0] == 'S' && buffer[1] == 'O')
			parse_south_path(v, buffer);
		else if (buffer[0] == 'S')
			parse_sprite_path(v, buffer);
		else if (buffer[0] == 'E' && buffer[1] == 'A')
			parse_east_path(v, buffer);
		else if (buffer[0] == 'W' && buffer[1] == 'E')
			parse_west_path(v, buffer);
		else if (buffer[0] == 'C')
			parse_ceiling_color(v, buffer);
		else if (buffer[0] == 'F')
			parse_floor_color(v, buffer);
		check = check_params(v);
		free(buffer);
	}
	if (check == 0)
		free(buffer);
	parse_map(v, fd);
	close(fd);
	return (0);
}

int	is_wspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

int	parse_floor_color(t_vars *v, char *str)
{
	int	i;
	int	res[3];
	int	cpt;

	i = 1;
	cpt = 0;
	while (cpt < 3)
	{
		res[cpt] = 0;
		while (is_wspace(str[i]))
			i++;
		while (ft_isdigit(str[i]))
		{
			res[cpt] = res[cpt] * 10 + str[i] - '0';
			i++;
		}
		if (str[i] == ',')
			i++;
		else if (cpt < 2)
			return (-1);
		cpt++;
	}
	v->floor = res[2] + 256 * res[1] + 256 * 256 * res[0];
	return (0);
}

int     parse_ceiling_color(t_vars *v, char *str)
{
        int     i;
        int	res[3];
        int     cpt;

        i = 1;
        cpt = 0;
        while (cpt < 3)
        {
                res[cpt] = 0;
                while (is_wspace(str[i]))
                        i++;
                while (ft_isdigit(str[i]))
		{
                        res[cpt] = res[cpt] * 10 + str[i] - '0';
			i++;
		}
		if (str[i] == ',')
                        i++;
                else if (cpt < 2)
                        return (-1);
		cpt++;
        }
        v->ceiling = res[2] + 256 * res[1] + 256 * 256 * res[0];
	return (0);
}

t_liste	*init_list(void)
{
	t_liste	*list;

	list = malloc(sizeof(t_list));
	if (list == NULL)
		return (NULL);
	list->start = NULL;
	return (list);
}

int	add_line_list(t_liste *list, char *buffer)
{
	t_line	*new;
	t_line	*current;

	new = malloc(sizeof(*new));
	if (list == NULL || new == NULL)
		return (-1);
	new->buffer = buffer;
	new->size = ft_strlen(buffer);
       	new->next = NULL;
	if (list->start == NULL)
		list->start = new;
	else
	{
		current = list->start;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = new;	
	}
	return (1);
}

int	print_list(t_liste *list)
{
	t_line	*current;

	if (list == NULL)
		return (-1);
	current = list->start;
	while (current != NULL)
	{
		printf("-> %s :: %d \n", current->buffer, current->size);
		current = current->next;
	}
	return (1);
}

int	get_map_size(t_vars *v, t_liste *l)
{
	t_line	*current;

	v->map_width = 0;
	v->map_height = 0;
	current = l->start;
	while(current != NULL)
	{
		v->map_height++;
		if (current->size > v->map_width)
			v->map_width = current->size;
		current = current->next;
	}
	return (0);
}

int	store_map(t_vars *v, t_liste *l)
{
	int	x;
	int	y;
	t_line	*current;

	if(!(v->map = (int**)malloc(sizeof(int*) * v->map_width)))
		return (-1);
	x = -1;
	while (++x < v->map_width)
	{
		if(!(v->map[x] = (int*)malloc(sizeof(int) * v->map_height)))
		       return (-1);
		current = l->start;
		y = 0;
		while (current != NULL)
		{
			if (current->size <= x)
				v->map[x][y] = ' ' - 48;
			else
				v->map[x][y] = current->buffer[x] - 48;
			current = current->next;
			y++;	
		}

	}	
	return (1);		
}

int     print_full_map(t_vars *v)
{
        int x;
        int y;

        y = -1;
        while (++y < v->map_height)
        {
                x = -1;
                while (++x < v->map_width)
		{
			if (v->map[x][y] == -16)
				printf("  ");
			else
                        	printf(" %d", v->map[x][y]);
		}
		printf("\n");
        }
        return (0);
}

int	init_player(t_vars *v, int x, int y, int a)
{
	v->posx = x;
	v->posy = y;
	if (a == NORTH || a == SOUTH)
		v->dirx = 0;
	if (a == NORTH)
		v->diry = -1;
	if (a == SOUTH)
		v->diry = 1;
	if (a == EAST || a == WEST)
		v->diry = 0;
	if (a == EAST)
		v->dirx = 1;
	if (a == WEST)
		v->dirx = -1;
	v->map[x][y] = 0;
	printf("player initialised in X = %d, Y = %d\n", x, y);
	return (0);
}

int	check_block(t_vars *v, int x, int y)
{
	int	a;

	a = v->map[x][y];
	if (a == 0 || a == 1 || a == 2 || a == (' ' - 48))
		return (1);
	else if ((a == NORTH || a == SOUTH || a == EAST || a == WEST) && (!(v->posx))) 
	{
		init_player(v, x, y, a);
		return (1);
	}
	else
		return (-1);	
}

int	check_sides(t_vars *v)
{
	int	x;
	int	y;

	x = -1;
	while (++x < v->map_width)
	{
		if (v->map[x][0] == 0 || v->map[x][0] == 2)
			return (-1);
		if (v->map[x][v->map_height - 1] == 0 || v->map[x][v->map_height - 1] == 2)
			return (-1);
	}
	y = -1;
	while (++y < v->map_height)
	{
		if (v->map[0][y] == 0 || v->map[0][y] == 2)
			return (-1);
		if (v->map[v->map_width - 1][y] == 0 || v->map[v->map_width - 1][y] == 2)
			return (-1);
	}
	return (1);
}

int	check_surround(t_vars *v, int x, int y)
{
	int	val[8];
	int	i;

	val[0] = v->map[x - 1][y - 1];
	val[1] = v->map[x][y - 1];
	val[2] = v->map[x + 1][y - 1];
	val[3] = v->map[x - 1][y];
	val[4] = v->map[x + 1][y];
	val[5] = v->map[x - 1][y + 1];
	val[6] = v->map[x][y + 1];
	val[7] = v->map[x + 1][y + 1];
	i = -1;
	while (++i < 8)
		if (val[i] != 1 && val[i] != 0 && val[i] != 2)
		      return (-1);
	return (1);	
}

int	check_closed(t_vars *v)
{
	int x;
        int y;


	if (check_sides(v) == -1)
		return (-1);
        y = 0;
        while (++y < v->map_height - 1)
        {
                x = 0;
                while (++x < v->map_width - 1)
                {
                        if (v->map[x][y] == 0 || v->map[x][y] == 2)
				if (check_surround(v, x, y) == -1)
					return (-1);
                }
        }
	return (1);
}

int	check_map(t_vars *v)
{
	int x;
	int y;

	y = -1;
	while (++y < v->map_height)
	{
		x = -1;
		while (++x < v->map_width)
		{
			if (check_block(v, x, y) == -1)
			{
				printf("wrong char inside map\n");
				return (-1);
			}
		}
	}
	if (check_closed(v) == -1)
	{
		printf("map error: map not closed\n");
		return (-1);
	}
	return (1);
}

int	free_list(t_liste *list)
{
	t_line	*current;
	t_line	*next;

	current = list->start;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	free(list);
	return (1);
}

int	parse_map(t_vars *v, int fd)
{
	char	*buffer;
	t_liste	*list;

	list = init_list();	
	while (get_next_line(fd, &buffer))
	{
		add_line_list(list, buffer);
	}
	add_line_list(list, buffer);
	//print_list(list);
	get_map_size(v, list);
	store_map(v, list);
	//print_full_map(v);
	if (check_map(v) == -1)
	{
		exit(0);
		return (-1);
	}
	free_list(list);
	return (1);
}
