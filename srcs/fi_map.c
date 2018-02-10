/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fi_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:31:35 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/10 18:59:39 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	**create_map(char **map, char *line, t_map *info)
{
	int		i;

	i = 0;
	info->height = ft_atoi(line + 8);
	//ft_printf("%d\n", info->height);
	if (!(map = malloc(sizeof(*map) * (info->height + 1))))
		return (NULL);
	info->width = ft_atoi(line + 9 + ft_intlen(info->height));
	//ft_printf("%d\n", info->width);
	get_next_line(0, &line);
	free(line);
	while (i < info->height)
	{
		get_next_line(0, &line);
		map[i] = ft_strsub(line, 4, info->width);
		//ft_printf("%d : %s\n", i, map[i]);
		free(line);
		i++;
	}
	map[i] = 0;
	return (map);
}

char		**get_map(char **map, char *line, t_map *info)
{
	int		i;

	i = 0;
	info->height = ft_atoi(line + 8);
	//ft_printf("%d\n", info->height);
	info->width = ft_atoi(line + 9 + ft_intlen(info->height));
	//ft_printf("%d\n", info->width);
	free(line);
	get_next_line(0, &line);
	//ft_printf("%s", line);
	free(line);
	while (i < info->height)
	{
		get_next_line(0, &line);
		ft_strcpy(map[i], line + 4);
		//ft_printf("%s\n", map[i]);
		free(line);
		i++;
	}
	return (map);
}
