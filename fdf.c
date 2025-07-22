/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 14:20:07 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 10:27:37 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars vars;

	ft_bzero(&vars, sizeof(t_vars));

	if (argc != 2)
	{
		printf("Usage: %s map.fdf\n", argv[0]);
		return (1);
	}
	vars.tab = parse_fdf(argv[1], &vars.height, &vars.width);
	if (!vars.tab)
		exit_fdf(&vars, "Error parse_fdf", 1);

	vars.mlx = mlx_init();
	if (!vars.mlx)
		exit_fdf(&vars, "Error mlx_init", 1);

	vars.win = mlx_new_window(vars.mlx, WIN_WIDTH, WIN_HEIGHT, "Mini FDF");
	if (!vars.win)
		exit_fdf(&vars, "Error mlx_new_window", 1);

	vars.zoom = 40;
	vars.offset_x = 0;
	vars.offset_y = 0;
	vars.angle = 0.523599;

	draw_map(&vars, vars.tab, vars.width, vars.height);

	mlx_key_hook(vars.win, handle_keypress, &vars);
	mlx_hook(vars.win, 17, 0, handle_close, &vars);
	mlx_expose_hook(vars.win, expose_hook, &vars);

	mlx_loop(vars.mlx);
	exit_fdf(&vars, NULL, 0);
	return (0);
}
