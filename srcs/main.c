/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:23 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/21 20:30:00 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		display_error(char *str)
{
	ft_dprintf(2, "%s\n", str);
	exit(0);
}

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
			create_map(&map, line);
		create_piece(&pi, line);
		algo_filler(&map, &pi);
		free_piece(&pi);
	}
	free_map(&map);
	return (0);
}
