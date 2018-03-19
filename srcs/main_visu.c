/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:13:55 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/17 13:54:11 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

Uint32      get_color(t_color c1, t_color c2, double k)
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

void		clean_quit(t_affi *disp)
{
	SDL_FreeSurface(disp->surface);
	SDL_DestroyWindow(disp->win);
	TTF_Quit();
	SDL_Quit();
	exit (0);
}
 
int			get_event(t_affi *disp, t_parse *info, t_turn *first, t_turn *last)
{

	int		i;
	int		j;

	if (disp->event.type == SDL_QUIT)
		clean_quit(disp);
	else if (disp->event.key.type == SDL_KEYDOWN)
	{
		if (disp->event.key.keysym.sym == SDLK_ESCAPE)
			clean_quit(disp);
		else if (disp->event.key.keysym.sym == SDLK_RETURN)
		{
			disp->current = first;
			draw_next(disp, info);
			disp->pause = 0;
		}
		else if (disp->event.key.keysym.sym == SDLK_o)
		{
			if (disp->k > 0.1)
			{
				disp->k -= 0.1;
				if (disp->current->next == NULL)
					draw_last(disp, info);
				else
					draw_next(disp, info);
			}
		}
		else if (disp->event.key.keysym.sym == SDLK_p)
		{
			if (disp->k < 0.8)
			{
				disp->k += 0.1;
				if (disp->current->next == NULL)
					draw_last(disp, info);
				else
					draw_next(disp, info);
			}
		}
		else if (disp->event.key.keysym.sym == SDLK_BACKSPACE)
		{
			disp->current = last;
			draw_last(disp, info);
		}
		else if (disp->event.key.keysym.sym == SDLK_RIGHT)
		{
			if (disp->current->next != NULL && disp->pause == 1)
			{
				disp->current = disp->current->next;
				draw_next(disp, info);
			}
			else
				draw_last(disp, info);
		}
		else if (disp->event.key.keysym.sym == SDLK_LEFT)
		{
			if (disp->current->prev != NULL && disp->pause == 1)
			{
				disp->current = disp->current->prev;
				draw_next(disp, info);
			}
		}
		else if (disp->event.key.keysym.sym == SDLK_SPACE)
		{
			if (disp->pause == 0)
				disp->pause = 1;
			else
				disp->pause = 0;
		}
		else
			return (0);
	}
	SDL_UpdateWindowSurface(disp->win);
	return (0);
}

void		get_win_infos(t_parse *info, t_affi *disp)
{
	disp->pixel = 11;
	disp->win_height = (disp->pixel + 1) * info->map_height + 1;
	disp->win_width = (disp->pixel + 1) * info->map_width + 1;
	while (disp->win_height < 500 || disp->win_width < 500)
	{
		disp->pixel++;
		disp->win_height = (disp->pixel + 1) * info->map_height + 1;
		disp->win_width = (disp->pixel + 1) * info->map_width + 1;
	}
	while (disp->win_height > 900 || disp->win_width > 900)
	{
		disp->pixel--;
		disp->win_height = (disp->pixel + 1) * info->map_height + 1;
		disp->win_width = (disp->pixel + 1) * info->map_width + 1;
	}
}

int			main(void)
{
	t_affi		disp;
	t_parse		info;
	t_turn		*first;
	t_turn		*last;
	t_turn		*current;
	TTF_Font	*font;
	char		str[200];
	int			i;
	SDL_Color	color = {255, 255, 255, 255};

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		display_error("Error : Init");
	if (TTF_Init() < 0)
		display_error("Error : Init");
    if (!(first = ft_memalloc(sizeof(t_turn) + 1)))
		display_error("malloc error");
    if (!(last = ft_memalloc(sizeof(t_turn) + 1)))
		display_error("malloc error");
	info = parser_visu(&disp, &current);
	disp.pause = 1;
	disp.grid = 0;
	disp.k = 0.;
	i = -1;
	first = current;
	first->next = current;
	first->prev = NULL;
	current->prev = first;
	disp.current = first;
	last = first;
	font = NULL;
	get_win_infos(&info, &disp);
	ft_sprintf(str, "%s vs %s", info.p1, info.p2);
	if (!(disp.win = SDL_CreateWindow(str, SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, disp.win_width, disp.win_height + 100, SDL_WINDOW_SHOWN)))
		return (-1);
	disp.surface = SDL_GetWindowSurface(disp.win);
	draw_next(&disp, &info);
	SDL_GL_SetSwapInterval(1);
	while (1)
	{
		while (SDL_PollEvent(&(disp.event)))
		{
			if (get_event(&disp, &info, first, last) == 0)
				break ;
		}
		if (!info.parse_finished)
		{
			current = next_turn(current, &info);
			last = current;
		}
		i += (!disp.pause);
		if (i == 0)
		{
			if (disp.current->next != NULL)
			{
				disp.current = disp.current->next;
				draw_next(&disp, &info);
				SDL_UpdateWindowSurface(disp.win);
			}
			else 
			{
				draw_last(&disp, &info);
				SDL_UpdateWindowSurface(disp.win);
				disp.pause = 1;
			}
			i = -1;
		}
	}
	clean_quit(&disp);
}
