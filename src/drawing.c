/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:54:38 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/20 23:12:42 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
        char    *dst;

        dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
        *(unsigned int*)dst = color;
}

void    draw_px_col(t_vars *v, int cpt)
{
        int     px;

        if (v->first_px > 0)
        {
                px = -1;
                while (++px < v->first_px)
                        my_mlx_pixel_put(&v->img, cpt, px, v->ceiling);
	}
        px = v->first_px - 1;
        while (++px < v->last_px)
                my_mlx_pixel_put(&v->img, cpt, px, RED);
        while (px < HEIGHT)
        {
                my_mlx_pixel_put(&v->img, cpt, px, v->floor);
		px++;
        }
}

int	get_px_color(t_data *img, int y, double preci, int w_height)
{
	char	*px;
	double	step;
	double	x_tex;
	double	y_tex;
	int	color;
	
	step = img->height / (double)w_height;
	x_tex = preci * (double)img->width;
	y_tex = (double)y * step;
	
	px = img->addr + ((int)y_tex * img->line_length + (int)x_tex * (img->bpp / 8));
	color = (unsigned int)*px;
	return (color);
}


void    draw_px_col2(t_vars *v, int cpt, char dir)
{
        int	px;
	int	y;
	int	color;
	t_data	**img;

	(void) dir;
	img = &v->img_no;
	/*if (dir == 'N')
		img = &v->img_no;
	else if (dir == 'S')
		img = &v->img_so;
	else if (dir == 'E')
		img = &v->img_ea;
	else
		img = &v->img_we;*/
        if (v->first_px > 0)
        {
                px = -1;
                while (++px < v->first_px)
                        my_mlx_pixel_put(&v->img, cpt, px, v->ceiling);
        }
	px = v->first_px - 1;
	y = 0;
        while (++px < v->last_px)
	{
		color = get_px_color(*img, y, v->wall_x - (int)v->wall_x, v->w_height);
		my_mlx_pixel_put(&v->img, cpt, px, color);
		y++;
	}
	while (px < HEIGHT)
        {
                my_mlx_pixel_put(&v->img, cpt, px, v->floor);
                px++;
        }
}

