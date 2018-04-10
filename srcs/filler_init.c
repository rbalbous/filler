/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:38:38 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/10 17:05:41 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_player	*get_dist(t_player *first, t_map *map, int *min_dist, int *belong)
{
	int		dist;

	dist = ft_abs(first->x - map->x) + ft_abs(first->y - map->y);
	if (*min_dist > dist || *min_dist == 0)
	{
		*min_dist = dist;
		*belong = first->belong;
	}
	else if (*min_dist == dist && first->belong != *belong)
		*belong = 'E';
	first = first->next;
	return (first);
}

void		check_dist(t_player *first, t_map *map)
{
	int		min_dist;
	int		belong;

	min_dist = 0;
	belong = 0;
	while (first != NULL)
	{
		first = get_dist(first, map, &min_dist, &belong);
	}
	map->al_map[map->y][map->x].belong = belong;
	map->al_map[map->y][map->x].dist = min_dist;
}

void		get_first_map(t_player *first, t_map *map)
{
	map->x = 0;
	while (map->x < map->width)
	{
		if (map->map[map->y][map->x] == '.')
		{
			check_dist(first, map);
		}
		else
		{
			map->al_map[map->y][map->x].belong = (1 * 'O' +
			(map->map[map->y][map->x] == 'X') * ('X' - 'O'));
			map->al_map[map->y][map->x].dist = 0;
		}
		map->x++;
	}
}

void		first_map(t_player *first, t_map *map)
{
	map->y = 0;
	if (!(map->al_map = malloc(sizeof(t_dots) * map->height + 1)))
		display_error("malloc_error");
	if (!(map->tmp_map = malloc(sizeof(t_dots) * map->height + 1)))
		display_error("malloc_error");
	while (map->y < map->height)
	{
		if (!((map->al_map)[map->y] = malloc(sizeof(t_dots*) * map->width)))
			display_error("malloc_error");
		if (!((map->tmp_map)[map->y] = malloc(sizeof(t_dots*) * map->width)))
			display_error("malloc_error");
		get_first_map(first, map);
		map->y++;
	}
}
