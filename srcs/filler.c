/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:03:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/01 00:40:58 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	filler_break(t_map *map, t_piece *pi)
{
	int		i;

	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
	i = 0;
	while (i < pi->height)
	{
		free(pi->piece[i]);
		i++;
	}
	free(pi->piece);
	exit(0);
}

int		abs(int x)
{
	x *= 1 - (x < 0) * 2;
	return (x);
}

int		min_dist(t_map *map, int ypiece, int xpiece)
{
	int		dist;
	int		x;
	int		y;

	y = 0;
	dist = (map->height + map->width) / 2;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == map->opponent && dist >
			abs(map->x + xpiece - x) + abs(map->y + ypiece - y))
			{
				dist = abs(map->x + xpiece - x) +
				abs(map->y + ypiece - y);
			}
			x++;
		}
		y++;
	}
	return (dist);
}

int		check_distance(t_map *map, t_piece *pi)
{
	int		ypiece;
	int		xpiece;
	int		tot_dist;

	ypiece = 0;
	tot_dist = 0;
	while (ypiece < pi->height)
	{
		xpiece = 0;
		while (xpiece < pi->width)
		{
			if (pi->piece[ypiece][xpiece] == '*')
				tot_dist += min_dist(map, ypiece, xpiece);
			xpiece++;
		}
		ypiece++;
	}
	return (tot_dist);
}

int		algo_filler(t_map *map, t_piece *pi)
{
	int		res;
	int		tot_dist;
	int		x_result;
	int		y_result;

	map->y = -pi->height;
	x_result = 0;
	y_result = 0;
	tot_dist = (map->height * map->width) / 2;
	while (map->y < map->height)
	{
		map->x = -pi->width;
		while (map->x < map->width)
		{
			res = place_piece(map, pi);
			if (tot_dist > res && res != 0)
			{
				x_result = map->x;
				y_result = map->y;
				tot_dist = res;
			}
			map->x++;
		}
		map->y++;
	}
	ft_printf("%d %d\n", y_result, x_result);
	return (0);
}

int		place_piece(t_map *map, t_piece *pi)
{
	int		ypiece;
	int		xpiece;
	int		disp;

	disp = 0;
	ypiece = 0;
	while (ypiece < pi->height)
	{
		xpiece = 0;
		while (xpiece < pi->width)
		{
			if (pi->piece[ypiece][xpiece] == '*')
			{
				if (map->y + ypiece < 0 || map->x + xpiece < 0 || map->y +
				ypiece > map->height - 1 || map->x + xpiece > map->width - 1
				|| map->map[map->y + ypiece][map->x + xpiece] == map->opponent)
					return (0);
				if (map->map[map->y + ypiece][map->x + xpiece] == map->player)
					disp++;
			}
			xpiece++;
		}
		ypiece++;
	}
	if (disp == 1)
		return (check_distance(map, pi));
	return (0);
}
