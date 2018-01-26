/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:23 by rbalbous          #+#    #+#             */
/*   Updated: 2018/01/26 18:51:59 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main()
{
	t_map	info;
	char	*line;
	char	**map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	info = (t_map){0, 0};
	get_next_line(0, &line);
	free(line);
	get_next_line(0, &line);
	map = malloc(1);
	create_map(map, line, &info);
	free(line);
	while (1)
	{
		j = 0;
		get_next_line(0, &line);
		free(line);
		while (j < info.width)
		{
			map[i][j] = line[j + 4];
			j++;
		}
		i++;
		free(line);
		ft_printf("%d %d\n", i, i);
		break ;	
	}
	return (IWAN);
}
