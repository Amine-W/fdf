/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 18:44:10 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 12:27:57 by amwahab          ###   ########.fr       */
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
	int z;
	int color;
}	t_point;

typedef struct s_vars {
    void	*mlx;
    void	*win;
    int		zoom;
    int		offset_x;
    int		offset_y;
    t_point		**tab;
    int		width;
    int		height;
	double	angle;
	int		dragging;
	int		last_x;
}	t_vars;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// draw.c
void	draw_map(t_vars *vars, t_point **tab, int width, int height);
void	draw_line(void *mlx, void *win, int x0, int y0, int x1, int y1, int color);
int gradient_realistic(int z, int zmin, int zmax);
void	get_z_min_max(t_point **tab, int width, int height, int *zmin, int *zmax);

// controls.c
int		handle_keypress(int keycode, void *param);
int		handle_close(void *param);
int		expose_hook(void *param);
int mouse_press(int button, int x, int y, void *param);
int mouse_release(int button, int x, int y, void *param);
int mouse_move(int x, int y, void *param);


// parse.c
t_point		**parse_fdf(const char *filename, int *height, int *width);
void	free_tab(t_point **tab, int height);

// utils
void	exit_fdf(t_vars *vars, char *msg, int exit_code);


#endif