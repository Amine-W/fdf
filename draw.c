/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:41:18 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 01:17:41 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
	int dx, dy, sx, sy, err, e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);

	if (x0 < x1)
		sx = 1;
	else
		sx = -1;

	if (y0 < y1)
		sy = 1;
	else
		sy = -1;

	err = dx - dy;

	while (1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

void draw_map(t_vars *vars, int **tab, int width, int height)
{
	int	i;
	int	j;
	int zmin;
	int zmax;
	int max_z;
	t_point points[1000][1000];

	get_z_min_max(tab, width, height, &zmin, &zmax);

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			double x = j;
			double y = i;
			points[i][j].x = (int)((x - y) * cos(ISO_ANGLE) * vars->zoom + 200 + vars->offset_x);
			points[i][j].y = (int)((x + y) * sin(ISO_ANGLE) * vars->zoom - tab[i][j] + 200 + vars->offset_y);
			j++;
		}
		i++;
	}

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (j < width - 1)
			{
				if (tab[i][j] > tab[i][j + 1])
					max_z = tab[i][j];
				else
					max_z = tab[i][j + 1];
				draw_line(vars->mlx, vars->win,
					points[i][j].x, points[i][j].y,
					points[i][j + 1].x, points[i][j + 1].y,
					gradient_color(max_z, zmin, zmax));
			}
			if (i < height - 1)
			{
				if (tab[i][j] > tab[i + 1][j])
					max_z = tab[i][j];
				else
					max_z = tab[i + 1][j];
				draw_line(vars->mlx, vars->win,
					points[i][j].x, points[i][j].y,
					points[i + 1][j].x, points[i + 1][j].y,
					gradient_color(max_z, zmin, zmax));
			}
			j++;
		}
		i++;
	}
}

void get_z_min_max(int **tab, int width, int height, int *zmin, int *zmax)
{
	int i;
	int j;

	*zmin = tab[0][0];
	*zmax = tab[0][0];

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (tab[i][j] < *zmin)
				*zmin = tab[i][j];
			if (tab[i][j] > *zmax)
				*zmax = tab[i][j];
			j++;
		}
		i++;
	}
}

int gradient_color(int z, int zmin, int zmax)
{
	double ratio;
	int r, g, b;

	if (zmax == zmin)
		ratio = 0.0;
	else
		ratio = (double)(z - zmin) / (double)(zmax - zmin);

	if (ratio < 0.25)
	{
		r = 0;
		g = (int)(ratio / 0.25 * 255);
		b = 255;
	}
	else if (ratio < 0.5)
	{
		r = 0;
		g = 255;
		b = 255 - (int)((ratio - 0.25) / 0.25 * 255);
	}
	else if (ratio < 0.75)
	{
		r = (int)((ratio - 0.5) / 0.25 * 255);
		g = 255;
		b = 0;
	}
	else
	{
		r = 255;
		g = 255 - (int)((ratio - 0.75) / 0.25 * 255);
		b = 0;
	}
	return (r << 16) | (g << 8) | b;
}
