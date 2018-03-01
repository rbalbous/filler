/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:31:35 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/01 16:15:11 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		free_map(t_map *map)
{
	int		i;

	i = 0;
	while (i < map->height)
	{
		free(map->map[i]);
		i++;
	}
	free(map->map);
}

int			create_map(t_map *map, char *line)
{
	int		i;

	i = 0;
	get_next_line(0, &line);
	map->height = ft_atoi(line + 8);
	if (!(map->map = malloc(sizeof(*map->map) * (map->height + 1))))
		return (-1);
	map->width = ft_atoi(line + 9 + ft_intlen(map->height));
	free(line);
	get_next_line(0, &line);
	free(line);
	while (i < map->height)
	{
		get_next_line(0, &line);
		map->map[i] = ft_strsub(line, 4, map->width);
		free(line);
		i++;
	}
	map->map[i] = 0;
	return (1);
}

void		get_map(t_map *map, char *line)
{
	int		i;

	i = 0;
	get_next_line(0, &line);
	map->height = ft_atoi(line + 8);
	map->width = ft_atoi(line + 9 + ft_intlen(map->height));
	free(line);
	get_next_line(0, &line);
	free(line);
	while (i < map->height)
	{
		get_next_line(0, &line);
		ft_strcpy(map->map[i], line + 4);
		free(line);
		i++;
	}
}
