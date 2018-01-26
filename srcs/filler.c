/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:03:53 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/26 18:47:32 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	create_map(char **map, char *line, t_map *info)
{
	int		i;

	i = 0;
	ft_printf("%s\n", line);
	info->width = ft_atoi(line + 8);
	ft_printf("%d\n", info->width);
	if (!(map = malloc(sizeof(*map) * (info->width + 1))))
		return ;
	info->height = ft_atoi(line + 9 + ft_intlen(info->width));
	ft_printf("%d\n", info->height);
	while (i < info->height)
	{
		ft_printf("%s\n", line);
		get_next_line(0, &line);
		free(line);
		if (!(*map = malloc(sizeof(**map) * (info->height + 1))))
			return ;
		i++;
	}
}

int		filler(void)
{
	return (0);
}
