/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:20:07 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/08 20:01:51 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <stdio.h>

#define MALLOC_ERROR	1

#define WIN_WIDTH 2000
#define WIN_HEIGHT 2000
#define GRID_W 10
#define GRID_H 10
#define SPACING 40
#define OFFSET_X 100
#define OFFSET_Y 100

typedef struct s_point
{
	int x;
	int y;
} t_point;

typedef struct s_vars
{
	void *mlx;
	void *win;
} t_vars;

int	handle_keypress(int keycode, void *param)
{
	t_vars *vars = (t_vars *)param;

	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	return (0);
}

int	handle_close(void *param)
{
	t_vars *vars = (t_vars *)param;

	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	return (0);
}

void	draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		mlx_pixel_put(mlx, win, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		int e2 = 2 * err;
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

int	main(void)
{
	t_vars vars;

	vars.mlx = mlx_init();
	if (!vars.mlx)
		return (MALLOC_ERROR);

	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini FDF");
	if (!vars.win)
	{
		mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		return (MALLOC_ERROR);
	}

	t_point points[GRID_H][GRID_W];

	for (int i = 0; i < GRID_H; i++)
	{
		for (int j = 0; j < GRID_W; j++)
		{
			points[i][j].x = j * SPACING + OFFSET_X;
			points[i][j].y = i * SPACING + OFFSET_Y;
		}
	}

	for (int i = 0; i < GRID_H; i++)
	{
		for (int j = 0; j < GRID_W; j++)
		{
			if (j < GRID_W - 1)
				draw_line(vars.mlx, vars.win, points[i][j].x, points[i][j].y,
					points[i][j + 1].x, points[i][j + 1].y, 0x00FFDE);
			if (i < GRID_H - 1)
				draw_line(vars.mlx, vars.win, points[i][j].x, points[i][j].y,
					points[i + 1][j].x, points[i + 1][j].y, 0x00FF56);
		}
	}

	mlx_key_hook(vars.win, handle_keypress, &vars);
	mlx_hook(vars.win, 17, 0, handle_close, &vars);
	mlx_loop(vars.mlx);

	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
	return (0);
}
