/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 13:38:38 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/07 19:51:46 by rbalbous         ###   ########.fr       */
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

void		print_list(t_player *first)
{
	while (first->next != NULL)
	{
		//ft_printf("%d %d %c\n", first->y, first->x, first->belong);
		first = first->next;
	}
	//ft_printf("%d %d %c\n", first->y, first->x, first->belong);
}

void		check_dist(t_player *first, t_map *map, int x, int y)
{
	int		dist;
	int	 	min_dist;
	int		belong;

	dist = 0;
	min_dist = 0;
	belong = 0;
	while (first->next != NULL)
	{
		dist = abs(first->x - x) + abs(first->y - y);
		if (min_dist > dist || min_dist == 0)
		{
			min_dist = dist;
			belong = first->belong;
		}
		else if (min_dist == dist && first->belong != belong)
			belong = 'E';
		first = first->next;
	}
	dist = abs(first->x - x) + abs(first->y - y);
	if (min_dist > dist || min_dist == 0)
	{
		min_dist = dist;
		belong = first->belong;
	}
	else if (min_dist == dist && first->belong != belong)
		belong = 'E';
	map->al_map[y][x].belong = belong;
	map->al_map[y][x].dist = min_dist;
}

void		first_map(t_player *first, t_map *map)
{
	int		x;
	int		y;

	//ft_printf("start\n");
	if (!(map->al_map = malloc(sizeof(t_dots) * map->height + 1)))
		display_error("malloc_error");
	if (!(map->tmp_map = malloc(sizeof(t_dots) * map->height + 1)))
			display_error("malloc_error");
	y = 0;
	while (y < map->height)
	{
		if (!((map->al_map)[y] = malloc(sizeof(t_dots*) * map->width + 1)))
			display_error("malloc_error");
		if (!((map->tmp_map)[y] = malloc(sizeof(t_dots*) * map->width + 1)))
			display_error("malloc_error");
		x = 0;
		while (x < map->width)
		{
			if (map->map[y][x] == '.')
			{
				check_dist(first, map, x, y);
			}
			else
			{
				map->al_map[y][x].belong = (1 * 'O' + (map->map[y][x] == 'X') * ('X' - 'O'));
				map->al_map[y][x].dist = 0;
			}
			x++;
		}
		y++;
	}

}

void		print_almap(t_map *map)
{
	int		y;
	int		x;

	y = 0;
	ft_printf("la\n");
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%2c ", map->al_map[y][x].belong);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%2d ", map->al_map[y][x].dist);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void		init_list(t_map *map)
{
	t_player	*player;
	t_player	*first;
	int		x;
	int		y;

	if (!(player = malloc(sizeof(t_player) * 1)))
		display_error("malloc_error");
	player->next = NULL;
	first = NULL;
	y = 0;
	while (y < map->height - 1)
	{
		x = 0;
		while (x < map->width - 1)
		{
			if (map->map[y][x] == 'X' || map->map[y][x] == 'O')
			{
				if (!first)
				{
					get_first_link(player, x, y, map);
					first = player;
				}
				else
				{
					player = get_next_link(player, x, y, map);
					if (first->next == NULL)
						first->next = player;
				}
			}
			x++;
		}
		y++;
	}
	print_list(first);
	first_map(first, map);
	//print_almap(map);
}
