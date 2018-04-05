/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:03:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/23 18:41:29 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		abs(int x)
{
	x *= 1 - (x < 0) * 2;
	return (x);
}

int		min_dist(t_map *map, t_piece *pi)
{
	int		dist;
	int		x;
	int		y;

	y = 0;
	dist = map->height * map->width;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == map->opponent && dist >
			abs(map->x + pi->x - x) + abs(map->y + pi->y - y))
			{
				dist = abs(map->x + pi->x - x) +
				abs(map->y + pi->y - y);
			}
			x++;
		}
		y++;
	}
	return (dist);
}

int		check_distance(t_map *map, t_piece *pi)
{
	int		tot_dist;

	pi->y = 0;
	tot_dist = 0;
	while (pi->y < pi->height)
	{
		pi->x = 0;
		while (pi->x < pi->width)
		{
			if (pi->piece[pi->y][pi->x] == '*')
				tot_dist += min_dist(map, pi);
			pi->x++;
		}
		pi->y++;
	}
	return (tot_dist);
}

int		algo_filler(t_map *map, t_piece *pi)
{
	int		res;
	int		tot_dist;

	map->y = -pi->height;
	pi->x_result = 0;
	pi->y_result = 0;
	tot_dist = map->height * map->width;
	while (map->y < map->height)
	{
		map->x = -pi->width;
		while (map->x < map->width)
		{
			res = place_piece(map, pi);
			if (tot_dist > res && res != 0)
			{
				pi->x_result = map->x;
				pi->y_result = map->y;
				tot_dist = res;
			}
			map->x++;
		}
		map->y++;
	}
	ft_printf("%d %d\n", pi->y_result, pi->x_result);
	return (0);
}

int		place_piece(t_map *map, t_piece *pi)
{
	int		disp;

	disp = 0;
	pi->y = 0;
	while (pi->y < pi->height)
	{
		pi->x = 0;
		while (pi->x < pi->width)
		{
			if (pi->piece[pi->y][pi->x] == '*')
			{
				if (map->y + pi->y < 0 || map->x + pi->x < 0 || map->y +
				pi->y > map->height - 1 || map->x + pi->x > map->width - 1
				|| map->map[map->y + pi->y][map->x + pi->x] == map->opponent)
					return (0);
				if (map->map[map->y + pi->y][map->x + pi->x] == map->player)
					disp++;
			}
			pi->x++;
		}
		pi->y++;
	}
	if (disp == 1)
		return (check_distance(map, pi));
	return (0);
}
