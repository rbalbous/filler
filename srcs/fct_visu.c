/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_visu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:07:12 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/10 17:05:27 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		*ft_strcdup(const char *src, int c)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	while (src[++i])
	{
		if (src[i] == c)
			break ;
	}
	if ((dest = (char*)malloc(sizeof(*dest) * i + 1)) == 0)
		return (0);
	j = -1;
	while (++j < i)
		dest[j] = src[j];
	dest[i] = 0;
	return (dest);
}

Uint32		get_color(t_color c1, t_color c2, double k)
{
	int			i;
	t_color		c;

	i = -1;
	while (++i < 4)
		c.rgb[i] = c1.rgb[i] + (c2.rgb[i] - c1.rgb[i]) * k;
	return (c.color);
}

void		clean_quit(t_affi *disp)
{
	SDL_FreeSurface(disp->surface);
	SDL_DestroyWindow(disp->win);
	TTF_CloseFont(disp->font);
	TTF_Quit();
	SDL_Quit();
	exit(0);
}

SDL_Color	color_conv(unsigned int hexvalue)
{
	SDL_Color rgb_color;

	rgb_color.r = hexvalue >> 16;
	rgb_color.g = (hexvalue & 0x00ff00) >> 8;
	rgb_color.b = (hexvalue & 0x0000ff);
	rgb_color.a = 255;
	return (rgb_color);
}
