/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:14:57 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/12 12:12:12 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	free_piece(t_piece *pi)
{
	int	i;

	i = 0;
	while (i < pi->height)
	{
		free(pi->piece[i]);
		i++;
	}
	free(pi->piece);
}

void	create_piece(t_piece *pi)
{
	int		i;
	char	*line;

	i = 0;
	get_next_line(0, &line);
	pi->height = ft_atoi(line + 6);
	if (!(pi->piece = malloc(sizeof(*pi->piece) * (pi->height + 1))))
		display_error("malloc error");
	pi->width = ft_atoi(line + 7 + ft_intlen(pi->height));
	free(line);
	while (i < pi->height)
	{
		get_next_line(0, &line);
		pi->piece[i] = ft_strsub(line, 0, pi->width);
		free(line);
		i++;
	}
	pi->piece[i] = 0;
}
