/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:00:45 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/05 15:01:08 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		change_color(t_affi *disp, t_parse *info, int add)
{
	if (disp->k < 0.8 && add == 1)
	{
		disp->k += 0.1;
		if (disp->current->next != NULL)
			draw_next(disp, info);
		else
			draw_last(disp, info);
		put_score(disp, info);
	}
	else if (disp->k > 0.1 && add == 2)
	{
		disp->k -= 0.1;
		if (disp->current->next != NULL)
			draw_next(disp, info);
		else
			draw_last(disp, info);
		put_score(disp, info);
	}
}

void		disp_next(t_affi *disp, t_parse *info)
{
	if (disp->current->next != NULL && disp->pause == 1)
	{
		disp->current = disp->current->next;
		draw_next(disp, info);
	}
	else
		draw_last(disp, info);
	put_score(disp, info);
}

void		disp_last(t_affi *disp, t_parse *info)
{
	if (disp->current->prev != NULL && disp->pause == 1)
	{
		disp->current = disp->current->prev;
		draw_next(disp, info);
		put_score(disp, info);
	}
}

void		disp_start(t_affi *disp, t_parse *info, t_turn *first)
{
	disp->current = first;
	draw_next(disp, info);
	disp->pause = 0;
}

int			get_event(t_affi *disp, t_parse *info, t_turn *first)
{
	if (disp->event.type == SDL_QUIT)
		clean_quit(disp);
	else if (disp->event.key.type == SDL_KEYDOWN)
	{
		if (disp->event.key.keysym.sym == SDLK_ESCAPE)
			clean_quit(disp);
		else if (disp->event.key.keysym.sym == SDLK_RETURN)
			disp_start(disp, info, first);
		else if (disp->event.key.keysym.sym == SDLK_KP_MINUS)
			change_color(disp, info, 2);
		else if (disp->event.key.keysym.sym == SDLK_KP_PLUS)
			change_color(disp, info, 1);
		else if (disp->event.key.keysym.sym == SDLK_RIGHT)
			disp_next(disp, info);
		else if (disp->event.key.keysym.sym == SDLK_LEFT)
			disp_last(disp, info);
		else if (disp->event.key.keysym.sym == SDLK_SPACE)
			disp->pause = (disp->pause == 0);
		else
			return (0);
	}
	SDL_UpdateWindowSurface(disp->win);
	return (0);
}
