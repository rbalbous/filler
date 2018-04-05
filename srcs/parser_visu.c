/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:08:59 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/23 16:18:20 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		get_start_points(t_parse *info, t_turn **current)
{
	int		i;

	i = 0;
	if (!(*current = malloc(sizeof(t_turn) * 1)))
		display_error("malloc error");
	if (!((*current)->map = malloc(sizeof(char*) * (info->map_height + 1))))
		display_error("malloc error");
	(*current)->next = NULL;
	(*current)->prev = NULL;
	(*current)->turn_nb_p1 = 1;
	(*current)->turn_nb_p2 = 1;
	while (i < info->map_height)
	{
		next_line(0, &(*current)->map[i]);
		i++;
	}
	(*current)->map[i] = 0;
}

void		next_line(int fd, char **line)
{
	if (get_next_line(fd, line) == -1)
		display_error("Read error");
}

void		new_line(char **line, int i)
{
	if (i == 0 || i == 1)
		free(*line);
	next_line(0, line);
	if (i == 0 || i == 2)
		free(*line);
}

t_parse		parser_visu(t_affi *disp, t_turn **current)
{
	t_turn		list;
	t_parse		info;
	char		*line;
	int			i;

	i = -1;
	info.parse_finished = 0;
	check_players_header(&info, &line, i);
	free(line);
	next_line(0, &line);
	free(line);
	check_map(disp, &info, &line);
	next_line(0, &line);
	free(line);
	get_start_points(&info, current);
	return (info);
}
