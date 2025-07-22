/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:41:18 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 12:40:54 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
	int dx, dy, sx, sy, err, e2;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
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

void get_z_min_max(t_point **tab, int width, int height, int *zmin, int *zmax)
{
	int i, j;
	*zmin = tab[0][0].z;
	*zmax = tab[0][0].z;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (tab[i][j].z < *zmin)
				*zmin = tab[i][j].z;
			if (tab[i][j].z > *zmax)
				*zmax = tab[i][j].z;
			j++;
		}
		i++;
	}
}

int lerp(int a, int b, double t)
{
	return (int)(a + (b - a) * t);
}

int color_lerp(int c1, int c2, double t)
{
	int r1 = (c1 >> 16) & 0xFF;
	int g1 = (c1 >> 8) & 0xFF;
	int b1 = c1 & 0xFF;

	int r2 = (c2 >> 16) & 0xFF;
	int g2 = (c2 >> 8) & 0xFF;
	int b2 = c2 & 0xFF;

	int r = lerp(r1, r2, t);
	int g = lerp(g1, g2, t);
	int b = lerp(b1, b2, t);

	return (r << 16) | (g << 8) | b;
}

int gradient_realistic(int z, int zmin, int zmax)
{
	int deep_ocean = 0x000046;
	int shallow_ocean = 0x0096FF;
	int grass = 0x228B22;
	int dirt = 0xC2B280;
	int mountain = 0xDCDCDC;

	if (z <= 0)
	{
		double t = (zmin == 0) ? 0 : (double)(z - zmin) / (0 - zmin);
		return color_lerp(deep_ocean, shallow_ocean, t);
	}
	else if (z > 0 && z <= 5)
	{
		double t = (double)(z) / 5.0;
		return color_lerp(shallow_ocean, grass, t);
	}
	else if (z > 5 && z <= 20)
	{
		double t = (double)(z - 5) / 15.0;
		return color_lerp(grass, dirt, t);
	}
	else
	{
		double t = (zmax == 20) ? 0 : (double)(z - 20) / (zmax - 20);
		if (t > 1)
			t = 1;
		return color_lerp(dirt, mountain, t);
	}
}

void draw_map(t_vars *vars, t_point **tab, int width, int height)
{
	int i, j;
	int zmin, zmax, max_z;
	int color;
	t_point **points;

	points = (t_point **)malloc(sizeof(t_point *) * height);
	i = 0;
	while (i < height)
	{
		points[i] = (t_point *)malloc(sizeof(t_point) * width);
		i++;
	}

	get_z_min_max(tab, width, height, &zmin, &zmax);

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			double x = j;
			double y = i;
			points[i][j].x = (int)((x - y) * cos(vars->angle) * vars->zoom + 200 + vars->offset_x);
			points[i][j].y = (int)((x + y) * sin(vars->angle) * vars->zoom - tab[i][j].z + 200 + vars->offset_y);
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
				if (tab[i][j].z > tab[i][j + 1].z)
					max_z = tab[i][j].z;
				else
					max_z = tab[i][j + 1].z;

				if (tab[i][j].color != -1 && tab[i][j + 1].color != -1)
					color = tab[i][j].color;
				else if (tab[i][j].color != -1)
					color = tab[i][j].color;
				else if (tab[i][j + 1].color != -1)
					color = tab[i][j + 1].color;
				else
					color = gradient_realistic(max_z, zmin, zmax);

				draw_line(vars->mlx, vars->win,
						  points[i][j].x, points[i][j].y,
						  points[i][j + 1].x, points[i][j + 1].y,
						  color);
			}

			if (i < height - 1)
			{
				if (tab[i][j].z > tab[i + 1][j].z)
					max_z = tab[i][j].z;
				else
					max_z = tab[i + 1][j].z;

				if (tab[i][j].color != -1 && tab[i + 1][j].color != -1)
					color = tab[i][j].color;
				else if (tab[i][j].color != -1)
					color = tab[i][j].color;
				else if (tab[i + 1][j].color != -1)
					color = tab[i + 1][j].color;
				else
					color = gradient_realistic(max_z, zmin, zmax);

				draw_line(vars->mlx, vars->win,
						  points[i][j].x, points[i][j].y,
						  points[i + 1][j].x, points[i + 1][j].y,
						  color);
			}
			j++;
		}
		i++;
	}

	i = 0;
	while (i < height)
	{
		free(points[i]);
		i++;
	}
	free(points);
}
