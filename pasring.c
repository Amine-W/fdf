/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pasring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amwahab <amwahab@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 21:51:22 by amwahab           #+#    #+#             */
/*   Updated: 2025/07/22 00:45:06 by amwahab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char *line)
{
	int count;
	int in_word;
	int i;

	count = 0;
	in_word = 0;
	i = 0;
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
void	fill_row(int *row, char **split, int width)
{
	int x;

	x = 0;
	while (x < width)
	{
		row[x] = ft_atoi(split[x]);
		free(split[x]);
		x++;
	}
	free(split);
}

void	free_tab(int **tab, int y)
{
	int i;

	i = 0;
	while (i < y)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int **parse_fdf(const char *filename, int *height, int *width)
{
	int fd;
	char *line;
	int **tab;
	int y;

	*height = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (*height == 0)
			*width = count_words(line);
		(*height)++;
		free(line);
	}
	close(fd);
	tab = (int **)malloc(sizeof(int *) * (*height));
	if (!tab)
		return (NULL);
	fd = open(filename, O_RDONLY);
	y = 0;
	while (y < *height && (line = get_next_line(fd)))
	{
		tab[y] = (int *)malloc(sizeof(int) * (*width));
		if (!tab[y])
		{
			free_tab(tab, y);
			return (NULL);
		}
		fill_row(tab[y], ft_split(line, ' '), *width);
		free(line);
		y++;
	}
	close(fd);
	return (tab);
}
