/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 16:14:57 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/19 00:56:40 by rbalbous         ###   ########.fr       */
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

int		create_piece(t_piece *pi, char *line)
{
	int		i;

	i = 0;
	get_next_line(0, &line);
	pi->height = ft_atoi(line + 6);
	if (!(pi->piece = malloc(sizeof(*pi->piece) * (pi->height + 1))))
		return (-1);
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
	return (0);
}
