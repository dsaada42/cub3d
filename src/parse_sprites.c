/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsaada <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 16:06:10 by dsaada            #+#    #+#             */
/*   Updated: 2021/10/18 20:52:43 by dsaada           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     parse_north_path(t_vars *v, char *str)
{
        int     i;
        int     j;
        int     cpt;
        char    *res;

        cpt = 0;
        j = 0;
        i = 2;
        while(is_wspace(str[i]))
                i++;
        while(ft_isprint(str[i + cpt]) && !(is_wspace(str[i + cpt])))
                cpt++;
        if (!(res = malloc(sizeof(char) * (cpt + 1))))
                return (1);
        while(j < cpt)
        {
                res[j] = str[i + j];
                j++;
        }
        res[j] = '\0';
        v->north = res;
        return (0);
}

int     parse_south_path(t_vars *v, char *str)
{
        int     i;
        int     j;
        int     cpt;
        char    *res;

        cpt = 0;
        j = 0;
        i = 2;
        while(is_wspace(str[i]))
                i++;
        while(ft_isprint(str[i + cpt]) && !(is_wspace(str[i + cpt])))
                cpt++;
        if (!(res = malloc(sizeof(char) * (cpt + 1))))
                return (1);
        while(j < cpt)
        {
                res[j] = str[i + j];
                j++;
        }
        res[j] = '\0';
        v->south = res;
        return (0);
}

int     parse_east_path(t_vars *v, char *str)
{
        int     i;
        int     j;
        int     cpt;
        char    *res;

        cpt = 0;
        j = 0;
        i = 2;
        while(is_wspace(str[i]))
                i++;
        while(ft_isprint(str[i + cpt]) && !(is_wspace(str[i + cpt])))
                cpt++;
        if (!(res = malloc(sizeof(char) * (cpt + 1))))
                return (1);
        while(j < cpt)
        {
                res[j] = str[i + j];
                j++;
        }
        res[j] = '\0';
        v->east = res;
        return (0);
}

int     parse_west_path(t_vars *v, char *str)
{
        int     i;
        int     j;
        int     cpt;
        char    *res;

        cpt = 0;
        j = 0;
        i = 2;
        while(is_wspace(str[i]))
                i++;
        while(ft_isprint(str[i + cpt]) && !(is_wspace(str[i + cpt])))
                cpt++;
        if (!(res = malloc(sizeof(char) * (cpt + 1))))
                return (1);
        while(j < cpt)
        {
                res[j] = str[i + j];
                j++;
        }
        res[j] = '\0';
        v->west = res;
        return (0);
}

int     parse_sprite_path(t_vars *v, char *str)
{
        int     i;
        int     j;
        int     cpt;
        char    *res;

        cpt = 0;
        j = 0;
        i = 2;
        while(is_wspace(str[i]))
                i++;
        while(ft_isprint(str[i + cpt]) && !(is_wspace(str[i + cpt])))
                cpt++;
        if (!(res = malloc(sizeof(char) * (cpt + 1))))
                return (1);
        while(j < cpt)
        {
                res[j] = str[i + j];
                j++;
        }
        res[j] = '\0';
        v->sprite = res;
        return (0);
}

