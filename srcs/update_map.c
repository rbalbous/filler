/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 18:40:20 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/07 23:24:38 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		create_last_map(t_map *map)
{
	int		y;

	y = 0;
	if (!(map->last_map = malloc(sizeof(*map->last_map) * (map->height + 1))))
		display_error("malloc error");
	while (y < map->height - 1)
	{
		if (!((map->last_map)[y] = malloc(sizeof(map->last_map) * (map->width + 1))))
			display_error("malloc error");
		ft_memcpy(map->last_map[y], map->map[y], sizeof(map->last_map) * map->width);
		y++;
	}
}

void		copy_map(t_map *map)
{
	int		y;

	y = 0;
	while (y < map->height - 1)
	{
		ft_memcpy(map->last_map[y], map->map[y], sizeof(map->last_map) * map->width);
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

	y = 0;
	/*while (y < map->height - 1)
	{
		ft_printf("%s\n", map->last_map[y]);
		y++;
	}
	ft_printf("\n");
	y = 0;
	while (y < map->height - 1)
	{
		ft_printf("%s\n", map->map[y]);
		y++;
	}*/
	y = 0;
	//ft_printf("ca rentre la ? %d %d\n", map->height, map->width);
	while (y < map->height - 1)
	{
		x = 0;
		while (x < map->width - 1)
		{
			//ft_printf("wtf? %d %d\n", y, x);
			if (map->map[y][x] != map->last_map[y][x])
			{
				map->tmp_map[y][x].belong = map->map[y][x];
				map->tmp_map[y][x].dist = 0;
				map->current = map->map[y][x];
				//ft_printf("%c %d %d\n", map->tmp_map[y][x].belong, map->tmp_map[y][x].dist, map->current);
				//ft_printf("recur\n");
				recur_top(map, y - 1, x, 1);
				//ft_printf("recur2\n");
				recur_bot(map, y + 1, x, 1);
				//ft_printf("recur3\n");
				recur_left(map, y, x - 1, 1);
				//ft_printf("recur4\n");
				recur_right(map, y, x + 1, 1);
			}
			x++;
		}
		y++;
	}
	/*y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->tmp_map[y][x].belong == 'O')
				ft_printf(CYAN);
			if (map->tmp_map[y][x].belong == 'X')
				ft_printf(RED);
			ft_printf("%2d "RESET, map->tmp_map[y][x].dist);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	ft_printf("\n");
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->al_map[y][x].belong == 'O')
				ft_printf(CYAN);
			if (map->al_map[y][x].belong == 'X')
				ft_printf(RED);
			ft_printf("%2d "RESET, map->al_map[y][x].dist);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	ft_printf("\n");*/
	//ft_printf("ca arrive ici ?\n");
	copy_tmp(map);
}