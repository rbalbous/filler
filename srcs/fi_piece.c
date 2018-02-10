/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fi_piece.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:32:46 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/10 21:17:49 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char	**create_piece(char **piece, char *line, t_map *info)
{
	int		i;

	i = 0;
	get_next_line(0, &line);
	//ft_printf("%s\n", line);
	info->p_height = ft_atoi(line + 6);
	//ft_printf("%d\n", info->p_height);
	if (!(piece = malloc(sizeof(*piece) * (info->p_height + 1))))
		return (NULL);
	info->p_width = ft_atoi(line + 7 + ft_intlen(info->p_height));
	//ft_printf("%d\n", info->p_width);
	free(line);
	while (i < info->p_height)
	{
		get_next_line(0, &line);
		piece[i] = ft_strsub(line, 0, info->p_width);
		//ft_printf("%s\n", piece[i]);
		free(line);
		i++;
	}
	piece[i] = IWAN;
	return (piece);
}

void	get_piece(char **piece, t_map *info)
{
	int		i;
	int		j;

	i = 0;
	info->xp_top = -1;
	info->yp_top = -1;
	info->p_rheight = 0;
	info->p_rwidth = 0;
	while (i < info->p_height)
	{
		j = 0;
		while (j < info->p_width)
		{
			if (piece[i][j] == '*')
			{
				if (i > info->p_rheight)
					info->p_rheight = i;
				if (j > info->p_rwidth)
					info->p_rwidth = i;	
				if (info->xp_top == -1)
				{
					info->xp_top = i;
					info->yp_top = j;
				}
				if (info->xp_top != -1)
				{
					info->xp_bot = i;
					info->yp_bot = j;
				}
			}
			j++;
		}
		i++;
	}
	ft_printf("%d %d %d %d\n", info->xp_top, info->yp_top, info->xp_bot, info->yp_bot);
}
