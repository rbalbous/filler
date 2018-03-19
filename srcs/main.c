/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:23 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/19 00:56:45 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main(void)
{
	t_map	map;
	t_piece	pi;
	char	*line;

	map = (t_map){NULL, 0, 0, 0, 0, 'X', 'X', -1};
	pi = (t_piece){NULL, 0, 0, 0, 0, 0, 0};
	get_next_line(0, &line);
	if (ft_strcmp(line + 9, "p1") != 1)
		map.player = 'O';
	else
		map.opponent = 'O';
	free(line);
	while (1)
	{
		if (map.map)
			get_map(&map, line);
		else
			if (create_map(&map, line) == -1)
				return (-1);
		create_piece(&pi, line);
		algo_filler(&map, &pi);
		free_piece(&pi);
	}
	free_map(&map);
	return (0);
}
