#include "cub3d.h"
#include <math.h>

void line(t_vars *vars, int x,int y,int x2, int y2, int color) {
    int dx = x2 - x ;
    int dy = y2 - y ;
    int dx1 = 0, dy1 = 0, dx2 = 0, dy2 = 0 ;
    int longest = abs(dx) ;
    int shortest = abs(dy) ;

    if (dx < 0)
	dx1 = -1;
    else if (dx > 0)
	dx1 = 1;
    if (dy < 0)
	dy1 = -1;
    else if (dy > 0)
	dy1 = 1;
    if (dx < 0)
	dx2 = -1;
    else if (dx > 0)
	dx2 = 1;
    if (!(longest > shortest))
    {
        longest = abs(dy);
        shortest = abs(dx);
        if (dy < 0)
		dy2 = -1;
	else if (dy > 0)
		dy2 = 1;
        dx2 = 0;
    }
    int numerator = longest >> 1;
    for (int i=0;i<=longest;i++)
    {
        my_mlx_pixel_put(&vars->img, x, y, color) ;
        numerator += shortest;
        if (!(numerator < longest))
	{
            numerator -= longest;
            x += dx1;
            y += dy1;
        }
	else
	{
            x += dx2;
            y += dy2;
        }
    }
}
