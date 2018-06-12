/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_territory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:43:58 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/11 14:04:08 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		al_cpy(t_map *map)
{
	int		y;

	y = 0;
	while (y < map->height)
	{
		ft_memcpy(map->tmp_map[y], map->al_map[y], sizeof(t_dots) * map->width);
		y++;
	}
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
		ft_memcpy(map->tmp_map[y], map->al_map[y], sizeof(t_dots) * map->width);
		y++;
	}
	return (add_piece(map, pi));
}
