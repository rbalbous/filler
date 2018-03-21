/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:55:34 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/21 20:23:31 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		draw_next(t_affi *disp, t_parse *info)
{
	int		y;
	int		x;
	int		p;

	p = disp->pixel + 1;
	y = 0;
	put_rect((t_rect){0, 0, disp->win_height, disp->win_width}, get_color(
	(t_color){BACKGROUND_NIGHT}, (t_color){BACKGROUND_DAY}, disp->k), disp);
	while (y < info->map_height)
	{
		x = 0;
		while (x < info->map_width)
		{
			put_colors(disp, x, y);
			x++;
		}
		y++;
	}
}

void		put_colors(t_affi *disp, int x, int y)
{
	int		p;

	p = disp->pixel + 1;
	if (disp->current->map[y][x + 4] == 'X')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color(
		(t_color){P2_DAY}, (t_color){P2_NIGHT}, disp->k), disp);
	else if (disp->current->map[y][x + 4] == 'x')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color(
		(t_color){P2_LST_DAY}, (t_color){P2_LST_NIGHT}, disp->k), disp);
	else if (disp->current->map[y][x + 4] == 'O')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color(
		(t_color){P1_DAY}, (t_color){P1_NIGHT}, disp->k), disp);
	else if (disp->current->map[y][x + 4] == 'o')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((
	t_color){P1_LST_DAY}, (t_color){P1_LST_NIGHT}, disp->k), disp);
}

void		put_lst_colors(t_affi *disp, int x, int y)
{
	int		p;

	p = disp->pixel + 1;
	if (disp->current->map[y][x + 4] == 'X')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color(
		(t_color){P2_DAY}, (t_color){P2_NIGHT}, disp->k), disp);
	else if (disp->current->map[y][x + 4] == 'x')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color(
		(t_color){P2_DAY}, (t_color){P2_NIGHT}, disp->k), disp);
	else if (disp->current->map[y][x + 4] == 'O')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color(
		(t_color){P1_DAY}, (t_color){P1_NIGHT}, disp->k), disp);
	else if (disp->current->map[y][x + 4] == 'o')
		put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color(
		(t_color){P1_DAY}, (t_color){P1_NIGHT}, disp->k), disp);
}

void		draw_last(t_affi *disp, t_parse *info)
{
	int		y;
	int		x;

	y = 0;
	put_rect((t_rect){0, 0, disp->win_height, disp->win_width}, get_color(
	(t_color){BACKGROUND_NIGHT}, (t_color){BACKGROUND_DAY}, disp->k), disp);
	while (y < info->map_height)
	{
		x = 0;
		while (x < info->map_width)
		{
			put_lst_colors(disp, x, y);
			x++;
		}
		y++;
	}
}
