/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_recur.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:02:18 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/10 17:56:16 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
