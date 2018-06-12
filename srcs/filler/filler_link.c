/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:42:09 by rbalbous          #+#    #+#             */
/*   Updated: 2018/05/07 16:43:50 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

t_player	*get_first_link(t_player *player, int x, int y, t_map *map)
{
	player->x = x;
	player->y = y;
	player->belong = map->map[y][x];
	player->next = NULL;
	return (player);
}

t_player	*get_next_link(t_player *player, int x, int y, t_map *map)
{
	t_player	*next;

	if (!(next = malloc(sizeof(t_player) * 1)))
		display_error("malloc_error");
	next->x = x;
	next->y = y;
	next->belong = map->map[y][x];
	next->next = NULL;
	player->next = next;
	return (next);
}

void		init_list2(t_map *map, t_player **player, t_player **first)
{
	map->x = 0;
	while (map->x < map->width - 1)
	{
		if (map->map[map->y][map->x] == 'X' || map->map[map->y][map->x] == 'O')
		{
			if (!*first)
				*first = get_first_link(*player, map->x, map->y, map);
			else
			{
				*player = get_next_link(*player, map->x, map->y, map);
				if ((*first)->next == NULL)
					(*first)->next = *player;
			}
		}
		map->x++;
	}
}

void		init_list(t_map *map)
{
	t_player	*player;
	t_player	*first;

	if (!(player = malloc(sizeof(t_player) * 1)))
		display_error("malloc_error");
	player->next = NULL;
	first = NULL;
	map->y = 0;
	while (map->y < map->height - 1)
	{
		init_list2(map, &player, &first);
		map->y++;
	}
	first_map(first, map);
	while (first != NULL)
	{
		player = first->next;
		free(first);
		first = player;
	}
}
