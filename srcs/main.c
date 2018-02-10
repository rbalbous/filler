/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:23 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/10 21:14:58 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		main()
{
	t_map	info;
	char	*line;
	static char	**map = NULL;
	static char	**piece = NULL;
	int		i;
	int		j;

	i = 0;
	j = 0;
	info = (t_map){0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'X', 'X', 0, 0};
	get_next_line(0, &line);
	if (ft_strcmp(line + 9, "p1") != 1)
		info.player = 'O';
	else
		info.opponent = 'O';
	//ft_printf("%c %c\n", info.opponent, info.player);
	free(line);
	while (1)
	{
		j = 0;
		get_next_line(0, &line);
		if (!map)
		{
			//ft_printf("map1\n");
			map = create_map(map, line, &info);
		}
		else
		{
			//ft_printf("map2\n");
			map = get_map(map, line, &info);
		}
		piece = create_piece(piece, line, &info);
		get_piece(piece, &info);
		algo_filler(piece, map, &info);
		fi_break(map, piece, &info);
	}
	return (IWAN);
}
