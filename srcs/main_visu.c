/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 15:13:55 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/21 20:27:34 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_win_infos(t_parse *info, t_affi *disp)
{
	disp->pixel = 11;
	disp->font_size = 45;
	disp->win_height = (disp->pixel + 1) * info->map_height + 1;
	disp->win_width = (disp->pixel + 1) * info->map_width + 1;
	while (disp->win_height < 500 || disp->win_width < 500)
	{
		disp->pixel++;
		if (disp->font_size > 35)
			disp->font_size--;
		disp->win_height = (disp->pixel + 1) * info->map_height + 1;
		disp->win_width = (disp->pixel + 1) * info->map_width + 1;
	}
	while (disp->win_height > 1400 || disp->win_width > 1400)
	{
		disp->pixel--;
		disp->win_height = (disp->pixel + 1) * info->map_height + 1;
		disp->win_width = (disp->pixel + 1) * info->map_width + 1;
	}
}

void		make_it_loop(t_affi disp, t_parse info, t_turn *current, int i)
{
	while (1)
	{
		while (SDL_PollEvent(&(disp.event)))
			if (get_event(&disp, &info, disp.first) == 0)
				break ;
		if (!info.parse_finished)
			current = next_turn(current, &info);
		i += (!disp.pause);
		if (i == 0)
		{
			if (disp.current->next != NULL)
			{
				disp.current = disp.current->next;
				draw_next(&disp, &info);
			}
			else
			{
				draw_last(&disp, &info);
				disp.pause = 1;
			}
			put_score(&disp, &info);
			SDL_UpdateWindowSurface(disp.win);
			i = -1;
		}
	}
}

void		init_disp(t_affi *disp, t_turn **current)
{
	if (!(disp->first = ft_memalloc(sizeof(t_turn) + 1)))
		display_error("malloc error");
	disp->first = *current;
	disp->first->next = *current;
	disp->first->prev = NULL;
	disp->first->turn_nb_p1 = 0;
	disp->first->turn_nb_p2 = 0;
	disp->current = disp->first;
	(*current)->prev = disp->first;
	disp->pause = 1;
	disp->grid = 0;
	disp->k = 0.;
	disp->last_event = 0;
	disp->font = TTF_OpenFont("arial.ttf", disp->font_size);
	if (!(disp->win = SDL_CreateWindow("Filler Visu", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, disp->win_width, disp->win_height + 100
	, SDL_WINDOW_SHOWN)))
		display_error("malloc error");
	disp->surface = SDL_GetWindowSurface(disp->win);
	SDL_UpdateWindowSurface(disp->win);
}

int			main(void)
{
	t_affi		disp;
	t_parse		info;
	t_turn		*current;
	SDL_Color	color;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		display_error("Error : Init");
	if (TTF_Init() < 0)
		display_error("Error : Init");
	info = parser_visu(&disp, &current);
	get_win_infos(&info, &disp);
	init_disp(&disp, &current);
	draw_next(&disp, &info);
	put_line(&disp, (t_point){0, disp.win_height},
	(t_point){disp.win_width, disp.win_height}, 0x404040);
	put_line(&disp, (t_point){0, disp.win_height + 1},
	(t_point){disp.win_width, disp.win_height + 1}, 0x404040);
	put_line(&disp, (t_point){0, disp.win_height + 2},
	(t_point){disp.win_width, disp.win_height + 2}, 0x404040);
	put_score(&disp, &info);
	SDL_GL_SetSwapInterval(1);
	make_it_loop(disp, info, current, -1);
	clean_quit(&disp);
}
