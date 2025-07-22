/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:51:22 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 11:45:41 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char *line)
{
	int count = 0;
	int in_word = 0;
	int i = 0;

	while (line[i])
	{
		if (line[i] != ' ' && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (line[i] == ' ')
			in_word = 0;
		i++;
	}
	return (count);
}

int	get_color(char *token)
{
	char *comma;
	
	comma = ft_strchr(token, ',');
	if (comma)
		return (ft_atoi_base(comma + 1, 16));
	return (-1);
}

void	fill_row(t_point *row, char **split, int width)
{
	int		x;
	char	**parts;

	x = 0;
	while (x < width)
	{
		if (split[x])
		{
			parts = ft_split(split[x], ',');
			row[x].z = ft_atoi(parts[0]);
			if (parts[1])
				row[x].color = ft_atoi_base(parts[1], 16);
			else
				row[x].color = -1;

			free(parts[0]);
			if (parts[1])
				free(parts[1]);
			free(parts);
			free(split[x]);
		}
		else
		{
			row[x].z = 0;
			row[x].color = -1;
		}
		x++;
	}
	free(split);
}


void	free_tab(t_point **tab, int y)
{
	int i = 0;
	while (i < y)
		free(tab[i++]);
	free(tab);
}

t_point **parse_fdf(const char *filename, int *height, int *width)
{
	int fd, y, current_width;
	char *line;
	char **split;
	t_point **tab;

	*height = 0;
	*width = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		current_width = count_words(line);
		if (*width == 0 || current_width > *width)
			*width = current_width;
		(*height)++;
		free(line);
	}
	close(fd);
	if (*height == 0 || *width == 0)
		return (NULL);

	tab = malloc(sizeof(t_point *) * (*height));
	if (!tab)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (free(tab), NULL);

	y = 0;
	while (y < *height && (line = get_next_line(fd)))
	{
		tab[y] = malloc(sizeof(t_point) * (*width));
		if (!tab[y])
			return (free(line), free_tab(tab, y), close(fd), NULL);
		split = ft_split(line, ' ');
		free(line);
		if (!split)
			return (free_tab(tab, y + 1), close(fd), NULL);
		fill_row(tab[y], split, *width);
		y++;
	}
	close(fd);
	return (tab);
}

