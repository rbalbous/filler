/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phoney_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 18:36:29 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/10 19:38:55 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			phoney_algo(t_map *map, t_piece *pi)
{
	map->y = -pi->height;
	while (map->y < map->height)
	{
		map->x = -pi->width;
		while (map->x < map->width)
		{
			if (place_pi(map, pi, map->x, map->y))
			{
				return (ft_printf("%d %d\n", map->y, map->x));
			}
			map->x++;
		}
		map->y++;
	}
	return (write(1, "0 0\n", 4));
}
