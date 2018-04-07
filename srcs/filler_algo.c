/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler_algo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/07 15:49:05 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/07 23:20:02 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		place_pi(t_map *map, t_piece *pi, int x, int y)
{
	int		disp;
	int		pi_y;
	int		pi_x;

	disp = 0;
	pi_y = 0;
	//ft_printf("start2\n");
	while (pi_y < pi->height)
	{
		pi_x = 0;
		while (pi_x < pi->width)
		{
			if (pi->piece[pi_y][pi_x] == '*')
			{
				//ft_printf("ahbon\n");
				if (y + pi_y < 0 || x + pi_x < 0 || y +
				pi_y > map->height - 1 || x + pi_x > map->width - 1
				|| map->map[y + pi_y][x + pi_x] == map->opponent)
					return (0);
				if (map->map[y + pi_y][x + pi_x] == map->player)
					disp++;
			}
			pi_x++;
		}
		pi_y++;
	}
	if (disp == 1)
		return (1);
	return (0);
}

void		recur_right(t_map *map, int y, int x, int dist)
{
	//ft_printf("recur_right y : %d x : %d\n", y, x);
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
	//ft_printf("recur_left y : %d x : %d\n", y, x);
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
	//ft_printf("recur_top y : %d x : %d\n", y, x);
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
	//ft_printf("recur_bot y : %d x : %d\n", y, x);
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

void		print_tmp_map(t_map *map)
{
	int		y;
	int		x;

	y = 0;
	//ft_printf("la\n");
	/*while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%2c ", map->tmp_map[y][x].belong);
			x++;
		}
		ft_printf("\n");
		y++;
	}
		ft_printf("\n");*/
	y = 0;
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
			//ft_printf("%c %d\n", map->tmp_map[y][x].belong, count);
			x++;
		}
		y++;
	}
	//ft_printf("%d\n", count);
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
	//ft_printf("add_piece\n");
	map->current = map->player;
	while (y < pi->height)
	{
		x = 0;
		while (x < pi->width)
		{
			if (pi->piece[y][x] == '*')
			{
				//ft_printf("star : %d %d\n", map->y + y, map->x + x);
				//ft_printf("recur\n");
				recur_top(map, map->y + y - 1, map->x + x, 1);
				//ft_printf("recur2\n");
				recur_bot(map, map->y + y + 1, map->x + x, 1);
				//ft_printf("recur3\n");
				recur_left(map, map->y + y, map->x + x - 1, 1);
				//ft_printf("recur4\n");
				recur_right(map, map->y + y, map->x + x + 1, 1);
				//ft_printf("ca passe la?\n");
			}
			x++;
		}
		y++;
	}
	//ft_printf("more\n");
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
	int		sol_x;
	int		sol_y;

	ter = 0;
	max_ter = -10000000;
	sol_x = 0;
	sol_y = 0;
	map->y = -pi->height;
	//ft_printf("start %d %d\n", map->height, map->width);
	while (map->y < map->height - 1)
	{
		map->x = -pi->width;
		while (map->x < map->width - 1)
		{
			//ft_printf("pk?\n");
			if (place_pi(map, pi, map->x, map->y))
			{
				//printf("valide %d %d\n", map->y, map->x);
				ter = get_most_territory(map, pi);
				//ft_printf("ter %d\n", ter);
				if (ter > max_ter)
				{
					max_ter = ter;
					sol_x = map->x;
					sol_y = map->y;
				}
				//print_tmp_map(map);
			}
			map->x++;
		}
		map->y++;
	}
	ft_printf("%d %d\n", sol_y, sol_x);
}