/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:54:29 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/20 23:12:48 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		init_vars(t_vars *v)
{
	v->next = 0;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, "Hello World!");
	if (v->dirx == 0)
	{
		v->planex = -0.66 * v->diry;
		v->planey = 0;
	}
	else
	{
		v->planex = 0;
		v->planey = 0.66 * v->dirx;
	}
	return (0);
}

int		generate_next_frame(t_vars *v)
{
	v->img.img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	v->img.addr = mlx_get_data_addr(v->img.img, &v->img.bpp,
		&v->img.line_length, &v->img.endian);
	get_dist(v);
	v->next = 1;
	return (0);
}

int		free_all(t_vars *v)
{
	int	x;

	x = -1;
	while (++x < v->map_width)
		free(v->map[x]);
	free(v->map);
	free(v->east);
	free(v->north);
	free(v->south);
	free(v->west);
	return (1);
}

int		keypress_handler(int keycode, t_vars *v)
{
	double old_dirx;
	double old_planex;

	if (keycode == ESCAPE)
	{
		mlx_destroy_window(v->mlx, v->win);
		exit(0);
	}
	else
	{
		if (keycode == W)
		{
			if (v->map[(int)(v->posx + v->dirx)][(int)(v->posy)] == 0)
				v->posx += v->dirx / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy + v->diry)] == 0)
				v->posy += v->diry / 10;
		}
		else if (keycode == S)
		{
			if (v->map[(int)(v->posx - v->dirx)][(int)(v->posy)] == 0)
				v->posx -= v->dirx / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy - v->diry)] == 0)
				v->posy -= v->diry / 10;
		}
		else if (keycode == D)
		{
			if (v->map[(int)(v->posx - v->diry)][(int)(v->posy)] == 0)
				v->posx += -v->diry / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy + v->dirx)] == 0)
				v->posy += v->dirx / 10;
		}
		else if (keycode == A)
		{
			if (v->map[(int)(v->posx + v->diry)][(int)(v->posy)] == 0)
				v->posx += v->diry / 10;
			if (v->map[(int)(v->posx)][(int)(v->posy - v->dirx)] == 0)
				v->posy += -v->dirx / 10;
		}
		else if (keycode == RIGHT)
		{
			old_dirx = v->dirx;
			v->dirx = v->dirx * cos(ROTSPEED) - v->diry * sin(ROTSPEED);
			v->diry = old_dirx * sin(ROTSPEED) + v->diry * cos(ROTSPEED);
			old_planex = v->planex;
			v->planex = v->planex * cos(ROTSPEED) - v->planey * sin(ROTSPEED);
			v->planey = old_planex * sin(ROTSPEED) + v->planey * cos(ROTSPEED);
		}
		else if (keycode == LEFT)
		{
			old_dirx = v->dirx;
			v->dirx = v->dirx * cos(-ROTSPEED) - v->diry * sin(-ROTSPEED);
			v->diry = old_dirx * sin(-ROTSPEED) + v->diry * cos(-ROTSPEED);
			old_planex = v->planex;
			v->planex = v->planex * cos(-ROTSPEED) - v->planey * sin(-ROTSPEED);
			v->planey = old_planex * sin(-ROTSPEED) + v->planey * cos(-ROTSPEED);
		}
		generate_next_frame(v);
	}
	return (0);
}

int		render_next_frame(t_vars *v)
{
	if (v->next)
	{
		mlx_put_image_to_window(v->mlx, v->win, v->img.img, 0, 0);
		mlx_destroy_image(v->mlx, v->img.img);
		v->next = 0;
	}
	return (0);
}

int		get_textures(t_vars *v)
{
	v->img_no->img = mlx_xpm_file_to_image(v->mlx, v->north, &v->img_no->width, &v->img_no->height);
        v->img_no->addr = mlx_get_data_addr(v->img_no->img, &v->img_no->bpp,
                &v->img_no->line_length, &v->img_no->endian);
        /*v->img_we->img = mlx_xpm_file_to_image(v->mlx, v->west, &v->img_we->width, &v->img_we->height);
        v->img_we->addr = mlx_get_data_addr(v->img_we->img, &v->img_we->bpp,
                &v->img_we->line_length, &v->img_we->endian);
	v->img_so->img = mlx_xpm_file_to_image(v->mlx, v->south, &v->img_so->width, &v->img_so->height);
	v->img_so->addr = mlx_get_data_addr(v->img_so->img, &v->img_so->bpp,
                &v->img_so->line_length, &v->img_so->endian);
        v->img_ea->img = mlx_xpm_file_to_image(v->mlx, v->east, &v->img_ea->width, &v->img_ea->height);
        v->img_ea->addr = mlx_get_data_addr(v->img_ea->img, &v->img_ea->bpp,
                &v->img_ea->line_length, &v->img_ea->endian);*/
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_vars		v;

	if (argc != 2)
		return (0);
	else if (!(fd = open(argv[1] , O_RDONLY)))
		return (0);
	v.posx = 0;
	parser(fd, &v);
	init_vars(&v);
	get_textures(&v);
	generate_next_frame(&v);
	mlx_hook(v.win, 2, 1L << 0, keypress_handler, &v);
	mlx_loop_hook(v.mlx, render_next_frame, &v);
	mlx_loop(v.mlx);
	return (0);
}
