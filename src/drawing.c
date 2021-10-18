/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:54:38 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/19 01:47:09 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
        char    *dst;

        dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
        *(unsigned int*)dst = color;
}

void    draw_px_col(t_vars *v, int cpt, char dir)
{
        int     px;
	int	color;

	color = 0;
	if (dir == 'N')
		color = BLUE;
	else if (dir == 'S')
		color = RED;
	else if (dir == 'E')
		color = GREEN;
	else if (dir == 'W')
		color = 0x00AAAAAA;
        if (v->first_px > 0)
        {
                px = -1;
                while (++px < v->first_px)
                        my_mlx_pixel_put(&v->img, cpt, px, v->ceiling);
	}
        px = v->first_px - 1;
        while (++px < v->last_px)
                my_mlx_pixel_put(&v->img, cpt, px, color);
        while (px < HEIGHT)
        {
                my_mlx_pixel_put(&v->img, cpt, px, v->floor);
		px++;
        }
}

int	get_px_color(t_vars *v, int y, double preci, int w_height)
{
	char	*px;
	double	step;
	double	x_tex;
	double	y_tex;
	int	color;
	
	step = v->img_so->height / (double)w_height;
	x_tex = preci * (double)v->img_so->width;
	y_tex = (double)y * step;
	
	//printf("x_tex = %d, y_tex = %d\n", (int)x_tex, (int)y_tex);
	px = v->img_so->addr + ((int)y_tex * v->img_so->line_length + (int)x_tex * (v->img_so->bpp / 8));
	color = (unsigned int)*px;
	return (color);
}


void    draw_px_col2(t_vars *v, int cpt, char dir)
{
        int	px;
	int	y;
	double	prec;
	int	color;

	(void)dir;
	//hauteur du mur = v->w_height
        if (v->first_px > 0)
        {
                px = -1;
                while (++px < v->first_px)
                        my_mlx_pixel_put(&v->img, cpt, px, v->ceiling);
        }
	px = v->first_px - 1;
	prec = v->wall_x - (int)v->wall_x;
	printf("wallx = %f\n", v->wall_x);
	printf("prec = %f\n", prec);
	y = 0;
        while (++px < v->last_px)
	{
		color = get_px_color(v, y, prec, v->w_height);
		my_mlx_pixel_put(&v->img, cpt, px, color);
		y++;
	}
	while (px < HEIGHT)
        {
                my_mlx_pixel_put(&v->img, cpt, px, v->floor);
                px++;
        }
}

