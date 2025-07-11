/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   croix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:56:16 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/11 16:37:25 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_WIDTH 500
#define WIN_HEIGHT 800

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		zoom;
	int		color;
	int		frame_count;
}	t_vars;

void	get_origin(int width, int height, int origin[2])
{
	origin[0] = width / 2;
	origin[1] = height / 2;
}

void	draw_cross(t_vars *vars)
{
	int origin[2];
	int i;

	get_origin(WIN_WIDTH, WIN_HEIGHT, origin);
	mlx_clear_window(vars->mlx, vars->win);

	i = -1000;
	while (i <= 1000)
	{
		mlx_pixel_put(vars->mlx, vars->win, origin[0] + i * vars->zoom, origin[1], vars->color);
		mlx_pixel_put(vars->mlx, vars->win, origin[0], origin[1] + i * vars->zoom, vars->color);
		i++;
	}
}
int	update_loop(void *param)
{
	t_vars *vars = (t_vars *)param;

	vars->frame_count++;
	if (vars->frame_count >= 30)
	{
		vars->color += 500;
		if (vars->color > 0xFFFFFF)
			vars->color = 0x000000;
		vars->frame_count = 0;
	}

	draw_cross(vars);
	return (0);
}


int	handle_keypress(int keycode, void *param)
{
	t_vars *vars = (t_vars *)param;

	printf("Keycode: %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(0);
	}
	else if (keycode == 65451)
		vars->zoom += 1;
	else if (keycode == 65453 && vars->zoom > 1)
		vars->zoom -= 1;

	draw_cross(vars);
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

int	main(void)
{
	t_vars vars;

	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (0);

	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "CROIX");
	if (vars.win == NULL)
	{
		mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		return (0);
	}

	vars.zoom = 10;
	vars.color = 0xFF0000;
	vars.frame_count = 0;

	draw_cross(&vars);
	mlx_key_hook(vars.win, handle_keypress, &vars);
	mlx_hook(vars.win, 17, 0, handle_close, &vars);
	mlx_loop_hook(vars.mlx, update_loop, &vars);
	mlx_loop(vars.mlx);

	mlx_destroy_window(vars.mlx, vars.win);
	mlx_destroy_display(vars.mlx);
	free(vars.mlx);
	return (1);
}
