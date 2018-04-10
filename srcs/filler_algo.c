/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:49:05 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/09 23:10:14 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		abs(int x)
{
	x *= 1 - (x < 0) * 2;
	return (x);
}

int		place_pi(t_map *map, t_piece *pi, int x, int y)
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
				if (y + pi->y < 0 || x + pi->x < 0 || y +
				pi->y > map->height - 1 || x + pi->x > map->width - 1
				|| map->map[y + pi->y][x + pi->x] == map->opponent)
					return (0);
				if (map->map[y + pi->y][x + pi->x] == map->player)
					disp++;
			}
			pi->x++;
		}
		pi->y++;
	}
	if (disp == 1)
		return (1);
	return (0);
}

void		recur_right(t_map *map, int y, int x, int dist)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->tmp_map[y][x].dist == 0)
		return ;
	if (map->tmp_map[y][x].dist < dist)
		return ;
	if (map->tmp_map[y][x].dist == dist)
	{
		if (map->tmp_map[y][x].belong != map->current)
			map->tmp_map[y][x].belong = 'E';
		return ;
	}
	map->tmp_map[y][x].belong = map->current;
	map->tmp_map[y][x].dist = dist;
	recur_right(map, y, x + 1, dist + 1);
	recur_right(map, y - 1, x, dist + 1);
	recur_right(map, y + 1, x, dist + 1);
}

void		recur_left(t_map *map, int y, int x, int dist)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->tmp_map[y][x].dist == 0)
		return ;
	if (map->tmp_map[y][x].dist < dist)
		return ;
	if (map->tmp_map[y][x].dist == dist)
	{
		if (map->tmp_map[y][x].belong != map->current)
			map->tmp_map[y][x].belong = 'E';
		return ;
	}
	map->tmp_map[y][x].belong = map->current;
	map->tmp_map[y][x].dist = dist;
	recur_left(map, y, x - 1, dist + 1);
	recur_left(map, y - 1, x, dist + 1);
	recur_left(map, y + 1, x, dist + 1);
}

void		recur_top(t_map *map, int y, int x, int dist)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->tmp_map[y][x].dist == 0)
		return ;
	if (map->tmp_map[y][x].dist < dist)
		return ;
	if (map->tmp_map[y][x].dist == dist)
	{
		if (map->tmp_map[y][x].belong != map->current)
			map->tmp_map[y][x].belong = 'E';
		return ;
	}
	map->tmp_map[y][x].belong = map->current;
	map->tmp_map[y][x].dist = dist;
}

void		recur_bot(t_map *map, int y, int x, int dist)
{
	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
		return ;
	if (map->tmp_map[y][x].dist == 0)
		return ;
	if (map->tmp_map[y][x].dist < dist)
		return ;
	if (map->tmp_map[y][x].dist == dist)
	{
		if (map->tmp_map[y][x].belong != map->current)
			map->tmp_map[y][x].belong = 'E';
		return ;
	}
	map->tmp_map[y][x].belong = map->current;
	map->tmp_map[y][x].dist = dist;
	recur_bot(map, y, x + 1, dist + 1);
	recur_bot(map, y, x - 1, dist + 1);
	recur_bot(map, y + 1, x, dist + 1);
}

int			calc_territory(t_map *map)
{
	int		y;
	int		x;
	int		count;

	y = 0;
	count = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->tmp_map[y][x].belong == map->player)
				count++;
			if (map->tmp_map[y][x].belong == map->opponent)
				count--;
			x++;
		}
		y++;
	}
	return (count);
}

void		put_piece(t_map *map, t_piece *pi)
{
	int		y;
	int		x;

	y = 0;
	map->current = map->player;
	while (y < pi->height)
	{
		x = 0;
		while (x < pi->width)
		{
			if (pi->piece[y][x] == '*')
			{
				map->tmp_map[map->y + y][map->x + x].belong = map->player;
				map->tmp_map[map->y + y][map->x + x].dist = 0;
			}
			x++;
		}
		y++;
	}
}

int			add_piece(t_map *map, t_piece *pi)
{
	int		y;
	int		x;

	y = 0;
	put_piece(map, pi);
	map->current = map->player;
	while (y < pi->height)
	{
		x = 0;
		while (x < pi->width)
		{
			if (pi->piece[y][x] == '*')
			{
				recur_top(map, map->y + y - 1, map->x + x, 1);
				recur_bot(map, map->y + y + 1, map->x + x, 1);
				recur_left(map, map->y + y, map->x + x - 1, 1);
				recur_right(map, map->y + y, map->x + x + 1, 1);
			}
			x++;
		}
		y++;
	}
	return (calc_territory(map));
}

int			get_most_territory(t_map *map, t_piece *pi)
{
	int		y;

	y = 0;
	while (y < map->height)
	{
		memcpy(map->tmp_map[y], map->al_map[y], sizeof(t_dots) * map->width);
		y++;
	}
	return (add_piece(map, pi));
}

void		filler_algo(t_map *map, t_piece *pi)
{
	int		max_ter;
	int		ter;

	ter = 0;
	max_ter = -10000000;
	map->y = -pi->height;
	while (map->y < map->height - 1)
	{
		map->x = -pi->width;
		while (map->x < map->width - 1)
		{
			if (place_pi(map, pi, map->x, map->y))
			{
				ter = get_most_territory(map, pi);
				if (ter > max_ter)
				{
					max_ter = ter;
					pi->x_result = map->x;
					pi->y_result = map->y;
				}
			}
			map->x++;
		}
		map->y++;
	}
	ft_printf("%d %d\n", pi->y_result, pi->x_result);
}
