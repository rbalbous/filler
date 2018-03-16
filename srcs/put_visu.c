/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_visu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:11:09 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/16 20:08:11 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		put_rect(t_rect rect, Uint32 color, t_affi *disp)
{
	int		min_width;
	int		min_length;
	
	min_length = 0;
	while (rect.length > min_length)
	{
		min_width = 0;
		while (rect.width > min_width)
		{
			put_pixel(rect.x + min_width, rect.y + min_length, color, disp);
			min_width++;;
		}
		min_length++;
	}
}

void    put_line(t_affi *disp, t_point start, t_point end, Uint32 color)
{
    t_point        d;
    t_point        s;
    int            err1;
    int            err2;

    d.x = ft_abs(start.x - end.x);
    d.y = ft_abs(start.y - end.y);
    s.x = -1 + 2 * (start.x < end.x);
    s.y = -1 + 2 * (start.y < end.y);
    err1 = ((d.x > d.y) * d.x + (d.x <= d.y) * -d.y) / 2;
    while (1)
    {
        put_pixel(start.x, start.y, color, disp);
        if (start.x == end.x && start.y == end.y)
            break ;
        err2 = err1;
        err1 -= d.y * (err2 > -d.x);
        start.x += s.x * (err2 > -d.x);
        err1 += d.x * (err2 < d.y);
        start.y += s.y * (err2 < d.y);
    }
}

void		put_pixel(int x, int y, Uint32 color, t_affi *disp)
{
	((Uint32*)disp->surface->pixels)[y * disp->surface->w + x] = color;
}

void		draw_next(t_affi *disp, t_parse *info)
{
	int		y;
	int		x;
	int		p;

	p = disp->pixel + 1;
	put_rect((t_rect){0, 0, disp->win_height, disp->win_width}, get_color((t_color){BACKGROUND_NIGHT}, (t_color){BACKGROUND_DAY}, disp->k), disp);
	y = 0;
	while (y < info->map_height)
	{
		x = 0;
		while (x < info->map_width)
		{
			if (disp->current->map[y][x + 4] == 'X')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P2_DAY}, (t_color){P2_NIGHT}, disp->k), disp);
			else if (disp->current->map[y][x + 4] == 'x')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P2_LST_DAY}, (t_color){P2_LST_NIGHT}, disp->k), disp);
			else if (disp->current->map[y][x + 4] == 'O')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P1_DAY}, (t_color){P1_NIGHT}, disp->k), disp);
			else if (disp->current->map[y][x + 4] == 'o')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P1_LST_DAY}, (t_color){P1_LST_NIGHT}, disp->k), disp);
			x++;
		}
		y++;
	}
}

void		draw_last(t_affi *disp, t_parse *info)
{
	int		y;
	int		x;
	int		p;

	p = disp->pixel + 1;
	put_rect((t_rect){0, 0, disp->win_height, disp->win_width}, get_color((t_color){BACKGROUND_NIGHT}, (t_color){BACKGROUND_DAY}, disp->k), disp);
	y = 0;
	while (y < info->map_height)
	{
		x = 0;
		while (x < info->map_width)
		{
			if (disp->current->map[y][x + 4] == 'X')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P2_DAY}, (t_color){P2_NIGHT}, disp->k), disp);
			else if (disp->current->map[y][x + 4] == 'x')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P2_DAY}, (t_color){P2_NIGHT}, disp->k), disp);
			else if (disp->current->map[y][x + 4] == 'O')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P1_DAY}, (t_color){P1_NIGHT}, disp->k), disp);
			else if (disp->current->map[y][x + 4] == 'o')
				put_rect((t_rect){x * p + 1, y * p + 1, p - 1, p - 1}, get_color((t_color){P1_DAY}, (t_color){P1_NIGHT}, disp->k), disp);
			x++;
		}
		y++;
	}
}
