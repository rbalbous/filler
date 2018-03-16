/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_visu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:08:59 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/16 17:09:10 by rbalbous         ###   ########.fr       */
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
	while (i < info->map_height)
	{
		next_line(0, &(*current)->map[i]);
		i++;
	}
	(*current)->map[i] = 0;
}

void		skip(char **line)
{
	int		i;
	int		pi_height;

	i = 0;
	pi_height = ft_atoi(*line + 6);
	free(*line);
	while (i < pi_height + 1)
	{
		next_line(0, line);
		free(*line);
		i++;
	}
	next_line(0, line);
}

int			check_link(t_parse *info, char *line)
{
	next_line(0, &line);
	while (ft_strncmp("Piece", line, 5) == 0)
		skip(&line);
	free(line);
	next_line(0, &line);
	if (ft_strncmp("==", line, 2) == 0)
	{
		free(line);
		info->parse_finished = 1;
		return (0);
	}
	free(line);
	return (1);
}

t_turn		*next_turn(t_turn *current, t_parse *info)
{
	t_turn		*new;
	char		*line;
	int			i;

	i = -1;
	if (!check_link(info, line))
		return (NULL);
	if (!(new = malloc(sizeof(t_turn) * 1)))
		display_error("malloc error");
	new->next = NULL;
	new->prev = current;
	current->next = new;
	if (!(new->map = malloc(sizeof(char*) * (info->map_height + 1))))
		display_error("malloc error");
	while (++i < info->map_height)
		next_line(0, &new->map[i]);
	new->map[i] = 0;
	current = new;
	return (current);
}

t_parse		parser_visu(t_affi *affi, t_turn **current)
{
	t_turn		list;
	t_parse		info;
	char		*line;

	info.parse_finished = 0;
	check_players_header(&info, &line);
	free(line);
	next_line(0, &line);
	free(line);
	check_map(affi, &info, &line);
	next_line(0, &line);
	free(line);
	get_start_points(&info, current);
	return (info);
}
