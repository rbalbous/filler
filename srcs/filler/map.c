/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:31:35 by rbalbous          #+#    #+#             */
/*   Updated: 2018/05/03 14:04:17 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	create_map(t_map *map)
{
	int		i;
	char	*line;

	i = 0;
	get_next_line(0, &line);
	map->height = ft_atoi(line + 8);
	if (!(map->map = malloc(sizeof(*map->map) * (map->height + 1))))
		display_error("malloc error");
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
	init_list(map);
	create_last_map(map);
}

void	get_map(t_map *map)
{
	int		i;
	char	*line;

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
	update_map(map);
	copy_map(map);
}
