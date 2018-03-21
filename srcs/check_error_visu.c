/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:45:45 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/21 20:30:51 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		display_error(char *str)
{
	ft_dprintf(2, "%s\n", str);
	exit(0);
}

static char g_header[5][49] = {
	"# -------------- VM  version 1.1 ------------- #",
	"#                                              #",
	"# 42 / filler VM Developped by: Hcao - Abanlin #",
	"#                                              #",
	"# -------------------------------------------- #"
};

void		check_players_header(t_parse *info, char **line, int i)
{
	while (++i < 5)
	{
		if (get_next_line(0, line) == -1 || ft_strcmp(*line, g_header[i]) != 0)
			display_error("Invalid file");
		free(*line);
	}
	next_line(0, line);
	if (**line != 'l')
		display_error("Bad player 1");
	else
	{
		if (!(info->p1 = ft_strcdup(strrchr(*line, '/') + 1, '.')))
			display_error("malloc error");
	}
	info->p1_len = ft_strlen(info->p1);
	free(*line);
	next_line(0, line);
	free(*line);
	next_line(0, line);
	if (**line != 'l')
		display_error("Bad player 2");
	else
		info->p2 = ft_strcdup(strrchr(*line, '/') + 1, '.');
	info->p2_len = ft_strlen(info->p2);
}

void		check_map(t_affi *disp, t_parse *info, char **line)
{
	(void)disp;
	next_line(0, line);
	info->map_height = ft_atoi(*line + 8);
	info->map_width = ft_atoi(*line + 9 + ft_intlen(info->map_height));
	free(*line);
	return ;
}
