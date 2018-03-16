/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:13:55 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/16 16:37:47 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		put_pixel(int x, int y, Uint32 color, t_affi *affi)
{
	((Uint32*)affi->surface->pixels)[y * affi->surface->w + x] = color;
}

void		put_rect(t_rect rect, Uint32 color, t_affi *affi)
{
	int		min_width;
	int		min_length;
	
	min_length = 0;
	while (rect.length > min_length)
	{
		min_width = 0;
		while (rect.width > min_width)
		{
			put_pixel(rect.x + min_width, rect.y + min_length, color, affi);
			min_width++;;
		}
		min_length++;
	}
}

Uint32        get_color(t_color c1, t_color c2, double k)
{
    int			i;
    t_color		c;

    i = -1;
    while (++i < 4)
		c.rgb[i] = c1.rgb[i] + (c2.rgb[i] - c1.rgb[i]) * k;
    return (c.color);
}

int        ft_abs(int x)
{
    x *= 1 - 2 * (x < 0);
    return (x);
}

void    put_line(t_affi *affi, t_point start, t_point end, Uint32 color)
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
        put_pixel(start.x, start.y, color, affi);
        if (start.x == end.x && start.y == end.y)
            break ;
        err2 = err1;
        err1 -= d.y * (err2 > -d.x);
        start.x += s.x * (err2 > -d.x);
        err1 += d.x * (err2 < d.y);
        start.y += s.y * (err2 < d.y);
    }
}

void		clean_quit(t_affi *affi)
{
	SDL_FreeSurface(affi->surface);
	SDL_DestroyWindow(affi->win);
    SDL_Quit();
	exit (0);
}

void		draw_next(t_affi *affi, t_parse *info)
{
	int		y;
	int		x;
	int		i;
	int		j;

	
	if (affi->grid >0)
	{
		if (affi->grid == 1)
		{
			i = 0;
			while (i < affi->win_height)
			{
				j = 0;
				while (j < affi->win_width)
				{
					put_line(affi, (t_point){j, 0}, (t_point){j, affi->win_height}, 0x78877e);
					j += affi->pixel + 1;
				}
				put_line(affi, (t_point){0, i}, (t_point){affi->win_width, i}, 0x78877e);
				i += affi->pixel + 1;
			}
			affi->grid = 2;
		}
	}
	else
		put_rect((t_rect){0, 0, affi->win_height, affi->win_width}, 0x000000, affi);
	y = 0;
	while (y < info->map_height)
	{
		x = 0;
		while (x < info->map_width)
		{
			if (affi->current->map[y][x + 4] == 'X')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0xff0000, affi);
			else if (affi->current->map[y][x + 4] == 'x')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0xff8080, affi);
			else if (affi->current->map[y][x + 4] == 'O')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0x0000ff, affi);
			else if (affi->current->map[y][x + 4] == 'o')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0x3399ff, affi);
			x++;
		}
		y++;
	}
}

void		draw_last(t_affi *affi, t_parse *info)
{
	int		y;
	int		x;
	int		i;
	int		j;

	put_rect((t_rect){0, 0, affi->win_height, affi->win_width}, 0x000000, affi);
	if (affi->grid == 1)
	{
		i = 0;
		while (i < affi->win_height)
		{
			j = 0;
			while (j < affi->win_width)
			{
				put_line(affi, (t_point){j, 0}, (t_point){j, affi->win_height}, 0x78877e);
				j += affi->pixel + 1;
			}
			put_line(affi, (t_point){0, i}, (t_point){affi->win_width, i}, 0x78877e);
			i += affi->pixel + 1;
		}
	}
	y = 0;
	while (y < info->map_height)
	{
		x = 0;
		while (x < info->map_width)
		{
			if (affi->current->map[y][x + 4] == 'X')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0xff0000, affi);
			else if (affi->current->map[y][x + 4] == 'x')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0xff0000, affi);
			else if (affi->current->map[y][x + 4] == 'O')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0x0000ff, affi);
			else if (affi->current->map[y][x + 4] == 'o')
				put_rect((t_rect){(x * (affi->pixel + 1)) + 1, (y * (affi->pixel + 1)) + 1, affi->pixel, affi->pixel}, 0x0000ff, affi);
			x++;
		}
		y++;
	}
}

void		get_event(t_affi *affi, t_parse *info, t_turn *first, t_turn *last)
{

	int		i;
	int		j;

	if (affi->event.type == SDL_QUIT)
		clean_quit(affi);
	else if (affi->event.key.type == SDL_KEYDOWN)
	{
		if (affi->event.key.keysym.sym == SDLK_ESCAPE)
			clean_quit(affi);
		if (affi->event.key.keysym.sym == SDLK_g)
		{
			affi->grid = 1;
			i = 0;
			while (i < affi->win_height)
			{
				j = 0;
				while (j < affi->win_width)
				{
					put_line(affi, (t_point){j, 0}, (t_point){j, affi->win_height}, 0x78877e);
					j += affi->pixel + 1;
				}
				put_line(affi, (t_point){0, i}, (t_point){affi->win_width, i}, 0x78877e);
				i += affi->pixel + 1;
			}
		}
		if (affi->event.key.keysym.sym == SDLK_r)
		{
			affi->grid = 0;
			i = 0;
			while (i < affi->win_height)
			{
				j = 0;
				while (j < affi->win_width)
				{
					put_line(affi, (t_point){j, 0}, (t_point){j, affi->win_height}, 0x000000);
					j += affi->pixel + 1;
				}
				put_line(affi, (t_point){0, i}, (t_point){affi->win_width, i}, 0x000000);
				i += affi->pixel + 1;
			}
		}
		if (affi->event.key.keysym.sym == SDLK_RETURN)
		{
			affi->current = first;
			draw_next(affi, info);
		}
		if (affi->event.key.keysym.sym == SDLK_BACKSPACE)
		{
			affi->current = last;
			affi->pause = 1;
			draw_last(affi, info);
		}
		if (affi->event.key.keysym.sym == SDLK_RIGHT)
		{
			if (affi->current->next != NULL)
			{
				affi->current = affi->current->next;
				draw_next(affi, info);
			}
			else
				draw_last(affi, info);
		}
		if (affi->event.key.keysym.sym == SDLK_LEFT)
		{
			if (affi->current->prev != NULL)
			{
				affi->current = affi->current->prev;
				draw_next(affi, info);
			}
		}
		if (affi->event.key.keysym.sym == SDLK_SPACE)
		{
			if (affi->pause == 0)
				affi->pause = 1;
			else
				affi->pause = 0;
		}
	}
	SDL_UpdateWindowSurface(affi->win);
}

void		get_win_infos(t_parse *info, t_affi *affi)
{
	affi->pixel = 11;
	affi->win_height = (affi->pixel + 1) * info->map_height + 1;
	affi->win_width = (affi->pixel + 1) * info->map_width + 1;
	while (affi->win_height < 500 || affi->win_width < 500)
	{
		affi->pixel++;
		affi->win_height = (affi->pixel + 1) * info->map_height + 1;
		affi->win_width = (affi->pixel + 1) * info->map_width + 1;
	}
}

int			main(void)
{
	t_affi		affi;
	t_parse		info;
	t_turn		*first;
	t_turn		*last;
	t_turn		*current;
	char		str[200];
	int			i;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		exit(0);
    if (!(first = ft_memalloc(sizeof(t_turn) + 1)))
		display_error("malloc error");
    if (!(last = ft_memalloc(sizeof(t_turn) + 1)))
		display_error("malloc error");
	info = parser_visu(&affi, &current);
	affi.pause = 1;
	affi.grid = 0;
	i = -1;
	first = current;
	first->next = current;
	first->prev = NULL;
	current->prev = first;
	affi.current = first;
	last = first;
	get_win_infos(&info, &affi);
	ft_sprintf(str, "%s vs %s", info.p1, info.p2);
	if (!(affi.win = SDL_CreateWindow(str, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, affi.win_width, affi.win_height, SDL_WINDOW_SHOWN)))
		return (-1);
	affi.surface = SDL_GetWindowSurface(affi.win);
	draw_next(&affi, &info);
	SDL_GL_SetSwapInterval(1);
	while (1)
	{
		while (SDL_PollEvent(&(affi.event)))
			get_event(&affi, &info, first, last);
		if (!info.parse_finished)
		{
			current = next_turn(current, &info);
			last = current;
		}
		i += (!affi.pause);
		if (i == 0)
		{
			if (affi.current->next != NULL)
			{
				affi.current = affi.current->next;
				draw_next(&affi, &info);
				SDL_UpdateWindowSurface(affi.win);	
			}
			else 
			{
				draw_last(&affi, &info);
				SDL_UpdateWindowSurface(affi.win);
				affi.pause = 1;
			}
			i = -1;
		}
	}
	clean_quit(&affi);
}
