/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   croix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 15:56:16 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/11 16:20:37 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIN_WIDTH 500
#define WIN_HEIGHT 800

typedef struct s_vars
{
	void *mlx;
	void *win;
}	t_vars;

void get_origin(int width, int height, int origin[2])
{
	origin[0] = width / 2;
	origin[1] = height / 2;
}

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

int	main(void)
{
	t_vars vars;
	int	origine[2];
	int	i;

	vars.mlx = mlx_init();
	if(vars.mlx == NULL)
	{
		mlx_destroy_display(vars.mlx);
		free(vars.mlx);
		return(0);
	}
	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "CROIX");
	if(vars.win == NULL)
	{
		mlx_destroy_window(vars.mlx, vars.win);
		free(vars.mlx);
		return(0);
	}

	// calculer les coordonees du centre de la fenetere
	get_origin(WIN_WIDTH, WIN_HEIGHT, origine);
	// placer un point au centre
	
	// tracer une ligne vers x -x y -y en partant du centre a chaque fois
	i = 0;
	while (i < WIN_HEIGHT)
	{
		mlx_pixel_put(vars.mlx, vars.win, origine[0], i, 0xFFFFFF); // blanc
		i++;
	}

	// Ligne horizontale
	i = 0;
	while (i < WIN_WIDTH)
	{
		mlx_pixel_put(vars.mlx, vars.win, i, origine[1], 0xFFFFFF); // blanc
		i++;
	}
	mlx_key_hook(vars.win, handle_keypress, &vars);
	mlx_hook(vars.win, 17, 0, handle_close, &vars);
	mlx_loop(vars.mlx);
	mlx_destroy_display(vars.mlx);
	mlx_destroy_window(vars.mlx, vars.win);
	free(vars.mlx);
	return(1);
}