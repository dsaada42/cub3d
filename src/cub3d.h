/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:25:02 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/19 00:50:20 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H
#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "get_next_line.h"
#include "../libft/libft.h"
#define ROTSPEED 0.1
#define MAPSIDE 8
#define	POSX 3
#define POSY 3
#define BLUE 0x000000FF
#define BLACK 0x00000000
#define WHITE 0x00FFFFFF
#define RED 0x00FF0000
#define GREEN 0x0000FF00
#define WIDTH 1920
#define HEIGHT 1080
#define NORTH 30
#define SOUTH 35
#define EAST 21
#define WEST 39
#define W 119
#define A 97
#define S 115
#define D 100
#define LEFT 65361
#define RIGHT 65363
#define ESCAPE 65307
#define PI 3.14159265359
#define P2 PI/2
#define P3 3*PI/2
#define	SIZE 64

typedef struct	s_line
{
	char		*buffer;
	int		size;
	struct s_line	*next;
}		t_line;

typedef struct	s_liste
{
	t_line	*start;
}		t_liste;

typedef struct  s_data
{
        void    *img;
        char    *addr;
        int     bpp;
        int     line_length;
        int     endian;
	int	width;
	int	height;
}               t_data;

typedef struct  s_vars
{
	int		w_height;
	int		floor;
        int		ceiling;
        char		*north;
        char		*east;
        char		*south;
        char		*west;
        char		*sprite;
        void    	*mlx;
        void    	*win;
        t_data  	img;
	t_data		*img_no;
	t_data		*img_so;
	t_data		*img_ea;
	t_data		*img_we;
	int		**map;
	int		map_width;
	int		map_height;
        int     	next;
	int		mapx;
	int		mapy;
	int		incx;
	int		incy;
	int		side;
	int		first_px;
	int		last_px;
	double		wall_x;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		ray_dirx;
	double		ray_diry;
	double		sidex;
	double		sidey;
	double		deltax;
	double		deltay;
	double		dist;

}               t_vars;

int     is_wspace(char c);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);
int     draw_map(t_vars *v, int *map);
int     draw_square(t_vars *v, int x, int y, int color);
void	line(t_vars *v, int x,int y,int x2, int y2, int color);
void	draw_rays(t_vars *v);
void    draw_px_col(t_vars *v, int cpt, char dir);
void    draw_px_col2(t_vars *v, int cpt, char dir);
int	parser(int fd, t_vars *v);
int     parse_resolution(t_vars *v, char *str);
int	parse_north_path(t_vars *v, char *str);
int     parse_south_path(t_vars *v, char *str);
int     parse_east_path(t_vars *v, char *str);
int     parse_west_path(t_vars *v, char *str);
int     parse_sprite_path(t_vars *v, char *str);
int     parse_floor_color(t_vars *v, char *str);
int     parse_ceiling_color(t_vars *v, char *str);
int	get_dist(t_vars *v);
int     parse_map(t_vars *v, int fd);

#endif
