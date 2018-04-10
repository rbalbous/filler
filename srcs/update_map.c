/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:40:20 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/10 19:34:25 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		create_last_map(t_map *map)
{
	int		y;

	y = 0;
	if (!(map->last_map = malloc(sizeof(char*) * (map->height + 1))))
		display_error("malloc error");
	while (y < map->height - 1)
	{
		if (!((map->last_map)[y] = malloc(sizeof(char) * (map->width + 1))))
			display_error("malloc error");
		ft_memcpy(map->last_map[y], map->map[y], sizeof(char) * map->width);
		y++;
	}
}

void		copy_map(t_map *map)
{
	int		y;

	y = 0;
	while (y < map->height - 1)
	{
		ft_memcpy(map->last_map[y], map->map[y], sizeof(char) * map->width);
		y++;
	}
}

void		copy_tmp(t_map *map)
{
	int		y;

	y = 0;
	while (y < map->height)
	{
		memcpy(map->al_map[y], map->tmp_map[y], sizeof(t_dots) * map->width);
		y++;
	}
}

void		update_map(t_map *map)
{
	int		y;
	int		x;

	y = -1;
	map->over = 1;
	while (++y < map->height - 1)
	{
		x = -1;
		while (++x < map->width - 1)
		{
			if (map->map[y][x] != map->last_map[y][x])
			{
				if (map->map[y][x] == map->opponent)
					map->over = 0;
				map->tmp_map[y][x].belong = map->map[y][x];
				map->tmp_map[y][x].dist = 0;
				map->current = map->map[y][x];
				recur_top(map, y - 1, x, 1);
				recur_bot(map, y + 1, x, 1);
				recur_left(map, y, x - 1, 1);
				recur_right(map, y, x + 1, 1);
			}
		}
	}
	copy_tmp(map);
}
