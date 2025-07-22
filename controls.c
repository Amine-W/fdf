/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 01:59:30 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 04:04:04 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int handle_keypress(int keycode, void *param)
{
	t_vars *vars = (t_vars *)param;

	if (keycode == 65307)
		exit_fdf(vars, "Exiting FDF", 0);
	else if ((keycode == 65451 || keycode == 61) && vars->zoom < 200)
		vars->zoom += 1;
	else if ((keycode == 65453 || keycode == 45) && vars->zoom > 2)
		vars->zoom -= 1;
	else if (keycode == 65363)
		vars->offset_x -= 20;
	else if (keycode == 65361)
		vars->offset_x += 20;
	else if (keycode == 65364)
		vars->offset_y -= 20;
	else if (keycode == 65362)
		vars->offset_y += 20;
	else if (keycode == 113)
		vars->angle -= 0.01;
	else if (keycode == 101)
		vars->angle += 0.01;
	if (vars->angle < 0)
		vars->angle = 0;
	if (vars->angle > M_PI)
		vars->angle = M_PI;
	mlx_clear_window(vars->mlx, vars->win);
	draw_map(vars, vars->tab, vars->width, vars->height);
	return (0);
}


int handle_close(void *param)
{
	t_vars *vars = (t_vars *)param;
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	return (0);
}



int expose_hook(void *param)
{
	t_vars *vars = (t_vars *)param;
	mlx_clear_window(vars->mlx, vars->win);
	draw_map(vars, vars->tab, vars->width, vars->height);
	return (0);
}
