/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:49:05 by rbalbous          #+#    #+#             */
/*   Updated: 2018/05/01 15:44:26 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			place_pi(t_map *map, t_piece *pi, int x, int y)
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

int			filler_algo(t_map *map, t_piece *pi)
{
	int		max_ter;
	int		ter;

	max_ter = -10000000;
	map->y = -pi->height - 1;
	while (++map->y < map->height)
	{
		map->x = -pi->width - 1;
		while (++map->x < map->width)
		{
			if (place_pi(map, pi, map->x, map->y))
			{
				if ((ter = get_most_territory(map, pi)) > max_ter)
				{
					max_ter = ter;
					pi->x_result = map->x;
					pi->y_result = map->y;
				}
			}
		}
	}
	al_cpy(map);
	return (ft_printf("%d %d\n", pi->y_result, pi->x_result));
}
