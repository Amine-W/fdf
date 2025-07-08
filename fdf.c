/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:20:07 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/08 17:44:06 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdlib.h>
#include <stdio.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
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

void draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx;
    int sy;

    if (x0 < x1)
        sx = 1;
    else
        sx = -1;

    if (y0 < y1)
        sy = 1;
    else
        sy = -1;

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

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "Mini FDF");

    t_point points[GRID_H][GRID_W];

    // Génération des points
    for (int i = 0; i < GRID_H; i++)
    {
        for (int j = 0; j < GRID_W; j++)
        {
            points[i][j].x = j * SPACING + OFFSET_X;
            points[i][j].y = i * SPACING + OFFSET_Y;
        }
    }

    // Dessin des lignes
    for (int i = 0; i < GRID_H; i++)
    {
        for (int j = 0; j < GRID_W; j++)
        {
            if (j < GRID_W - 1) // vers la droite
                draw_line(mlx, win, points[i][j].x, points[i][j].y,
                          points[i][j + 1].x, points[i][j + 1].y, 0x00FFDE);

            if (i < GRID_H - 1) // vers le bas
                draw_line(mlx, win, points[i][j].x, points[i][j].y,
                          points[i + 1][j].x, points[i + 1][j].y, 0x00FF56);
        }
    }
    mlx_loop(mlx);
    return (0);
}




