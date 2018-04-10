/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:23 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/10 19:39:30 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	display_error(char *str)
{
	ft_dprintf(2, "%s\n", str);
	exit(0);
}

int		main(void)
{
	t_map	map;
	t_piece	pi;
	char	*line;

	map = (t_map){0, 0, 0, 0, 0, 0, 0, 0, 0, 'X', 'X', 'E', 0};
	pi = (t_piece){NULL, 0, 0, 0, 0, 0, 0};
	get_next_line(0, &line);
	if (ft_strcmp(line + 9, "p1") != 1)
		map.player = 'O';
	else
		map.opponent = 'O';
	create_map(&map, line);
	while (1)
	{
		create_piece(&pi, line);
		if (map.over == 0)
			filler_algo(&map, &pi);
		else
		{
			phoney_algo(&map, &pi);
			get_map(&map);
		}
		free_piece(&pi);
	}
	return (0);
}
