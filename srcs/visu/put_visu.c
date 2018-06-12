/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_visu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:11:09 by rbalbous          #+#    #+#             */
/*   Updated: 2018/05/07 16:11:20 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		put_pixel(int x, int y, Uint32 color, t_disp *disp)
{
	((Uint32*)disp->surface->pixels)[y * disp->surface->w + x] = color;
}

void		put_rect(t_rect rect, Uint32 color, t_disp *disp)
{
	int		min_width;
	int		min_length;

	min_length = 0;
	while (min_length < rect.length)
	{
		min_width = 0;
		while (min_width < rect.width)
		{
			put_pixel(rect.x + min_width, rect.y + min_length, color, disp);
			min_width++;
		}
		min_length++;
	}
}

void		put_line(t_disp *disp, t_point start, t_point end, Uint32 color)
{
	t_point		d;
	t_point		s;
	int			err1;
	int			err2;

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

void		put_score(t_disp *disp, t_parse *info)
{
	char	str1[200];
	char	str2[200];

	put_rect((t_rect){0, disp->win_height + 3, 100, disp->win_width}, 0, disp);
	disp->message = SDL_GetWindowSurface(disp->win);
	ft_sprintf(str1, "(%d) %s", disp->current->turn_nb_p1, info->p1);
	disp->message = TTF_RenderText_Blended(disp->font, str1,
	color_conv(get_color((t_color){P1_DAY}, (t_color){P1_NIGHT}, disp->k)));
	disp->message2 = SDL_GetWindowSurface(disp->win);
	ft_sprintf(str2, "%s (%d)", info->p2, disp->current->turn_nb_p2);
	disp->message2 = TTF_RenderText_Blended(disp->font, str2,
	color_conv(get_color((t_color){P2_DAY}, (t_color){P2_NIGHT}, disp->k)));
	SDL_BlitSurface(disp->message, NULL, disp->surface, &(SDL_Rect)
	{(((disp->win_width + 6 * disp->pixel) / 2) -
	info->p1_len * disp->font_size) / 2 + disp->win_width / 2,
	disp->win_height + ((100 - disp->font_size) / 2),
	disp->win_width, 100});
	SDL_BlitSurface(disp->message2, NULL, disp->surface, &(SDL_Rect)
	{(((disp->win_width - 6 * disp->pixel) / 2) - info->p2_len) / 2,
	disp->win_height + ((100 - disp->font_size) / 2), disp->win_width, 100});
	SDL_FreeSurface(disp->message);
	SDL_FreeSurface(disp->message2);
}
