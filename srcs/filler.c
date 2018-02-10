/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:03:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/10 21:15:24 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	fi_break(char **map, char **piece, t_map *info)
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

int		algo_filler(char **piece, char **map, t_map *info)
{
	int		disp;

	info->x = 0;
	while (info->x < info->height)
	{
		info->y = 0;
		while (info->y < info->width)
		{
			//ft_printf("%c\n", map[i][j]);
			if (map[info->x][info->y] == info->player || map[info->x][info->y] == info->player + 32)
			{
				disp = fi_place_piece(map, piece, info);
				if (disp == 1)
					return (1);
			}
			info->y++;
		}
		info->x++;
	}
	ft_printf("0 0\n");
	return (0);
}

int		fi_place_piece(char **map, char **piece, t_map *info)
{
	int		ipiece;
	int		jpiece;
	int		disp;

	ipiece = info->x - info->xp_bot - info->xp_top;
	while (ipiece < info->x)
	{
		disp = 1;
		jpiece = info->y - info->yp_bot - info->xp_top;
		//ft_printf("%d %d %d %d %d %d\n", info->xp_bot, info->xp_top, i, j, ipiece, jpiece);
 		while (jpiece < info->x)
		{
			if ((!piece[ipiece][jpiece]) || ((piece[info->x - ipiece][info->y - jpiece] == info->player || piece[info->x - ipiece][info->y - jpiece] == info->player + 32) && (map[ipiece][jpiece] == 'x' || map[ipiece][jpiece] == 'o' || map[ipiece][jpiece] == 'X' || map[ipiece][jpiece] == 'O')))
				disp = 0;
			jpiece++;
		}
		ipiece++;
	}
	if (disp == 1)
	{
		ft_printf("%d %d\n", info->x, info->y);
		return (1);
	}
	return (0);
}
