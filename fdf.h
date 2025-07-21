/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:44:10 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 01:30:48 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include "Libft/libft.h"
# include "gnl/get_next_line.h"

# define ISO_ANGLE 0.523599
# define MALLOC_ERROR	1
# define WIN_WIDTH		2000
# define WIN_HEIGHT		2000

typedef struct s_point { 
	int x; 
	int y; 
}	t_point;

typedef struct s_vars {
    void	*mlx;
    void	*win;
    int		zoom;
    int		offset_x;
    int		offset_y;
    int		**tab;
    int		width;
    int		height;
}	t_vars;

// draw.c
void	draw_map(t_vars *vars, int **tab, int width, int height);
void	draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color);
int		gradient_color(int z, int zmin, int zmax);
void	get_z_min_max(int **tab, int width, int height, int *zmin, int *zmax);

// controls.c
int		handle_keypress(int keycode, void *param);
int		handle_close(void *param);
int		expose_hook(void *param);

// parse.c
int		**parse_fdf(const char *filename, int *height, int *width);
void	free_tab(int **tab, int height);

#endif