/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:03:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/24 17:41:11 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	filler_break(char **map, char **piece, t_map *info)
{
	int		i;

	i = 0;
	while (i < info->height)
	{
		free(map[i]);
		i++;
	}
	free(map);
	i = 0;
	while (i < info->height)
	{
		free(piece[i]);
		i++;
	}
	free(piece);
	exit(0);
}

int		abs(int x)
{
	x *= -1 + (x > 0) * 2;
	return (x);
}

int		get_min_dist(char **map, int ypiece, int xpiece, t_map *info)
{
	int		dist;
	int		x;
	int		y;

	y = 0;
	dist = (info->height + info->width) / 2;
	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if (map[y][x] == info->opponent && dist > abs((info->x + xpiece - x) * (info->y + ypiece - y)) / 2)
			{
				//ft_printf("%d\n", abs((info->x + xpiece - x) * (info->y + ypiece - y)) / 2);
				dist = abs((info->x + xpiece - x) * (info->y + ypiece - y)) / 2;
			}
			x++;
		}
		y++;
	}
	//ft_printf("dist : %d\n", dist);
	return (dist);
}

int		check_distance(char **map, char **piece, t_map *info)
{
	int		ypiece;
	int		xpiece;
	int		tot_dist;

	ypiece = 0;
	tot_dist = 0;
	while (ypiece < info->p_height)
	{
		xpiece = 0;
		while (xpiece < info->p_width)
		{
			if (piece[ypiece][xpiece] == '*')
				tot_dist += get_min_dist(map, ypiece, xpiece, info);
			xpiece++;
		}
		ypiece++;
	}
	return (tot_dist);
}

int		algo_filler(char **piece, char **map, t_map *info)
{
	int		disp;
	int		tot_dist;

	info->y = -info->p_height;
	tot_dist = (info->height * info->width) / 2;
	while (info->y < info->height)
	{
		info->x = -info->p_width;
		while (info->x < info->width)
		{
			disp = place_piece(map, piece, info);
			if (disp != 0)
			{
				if (tot_dist > disp)
				{
					info->x_result = info->x;
					info->y_result = info->y;
					//ft_printf("%d %d %d %d\n", tot_dist, disp, info->x_result, info->y_result);
					tot_dist = disp;
				}
			}
			info->x++;
		}
		info->y++;
	}
	ft_printf("%d %d\n", info->y_result, info->x_result);
	return (0);
}

int		place_piece(char **map, char **piece, t_map *info)
{
	int		ypiece;
	int		xpiece;
	int		disp;

	disp = 0;
	ypiece = 0;
	while (ypiece < info->p_height)
	{
		xpiece = 0;
		while (xpiece < info->p_width)
		{
			//ft_printf("ypiece : %d | xpiece : %d | info->x : %d | info->y : %d\n", ypiece, xpiece, info->x, info->y);
			if (piece[ypiece][xpiece] == '*')
			{
				if (info->y + ypiece < 0 || info->x + xpiece < 0 || info->y + ypiece > info->height - 1 || info->x + xpiece > info->width - 1)
					return (0);
				//ft_printf("%c %c\n", piece[ypiece][xpiece], map[info->y + ypiece][info->x + xpiece]);
				if (map[info->y + ypiece][info->x + xpiece] == info->player)
					disp++;
				if (map[info->y + ypiece][info->x + xpiece] == info->opponent)
					return (0);
			}
			xpiece++;
		}
		ypiece++;
	}
	//ft_printf("%d\n", disp);
	if (disp == 1)
	{
		//ft_printf("%d %d\n", info->y, info->x);
		//ft_dprintf(fd, "%d %d\n", info->y, info->x);
		return (check_distance(map, piece, info));
	}
	return (0);
}
