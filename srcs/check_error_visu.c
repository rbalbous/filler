/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_visu.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:45:45 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/16 16:20:51 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

char		*ft_strcdup(const char *src, int c)
{
	char	*dest;
	int		i;
	int		j;

	i = -1;
	while (src[++i])
	{
		if (src[i] == c)
			break ;
	}
	if ((dest = (char*)malloc(sizeof(*dest) * i + 1)) == 0)
		return (0);
	j = -1;
	while (++j < i)
		dest[j] = src[j];
	dest[i] = '\0';
	return (dest);
}

static char g_header[5][49] = {
	"# -------------- VM  version 1.1 ------------- #",
	"#                                              #",
	"# 42 / filler VM Developped by: Hcao - Abanlin #",
	"#                                              #",
	"# -------------------------------------------- #"
};

void		check_players_header(t_parse *info, char **line)
{
	int		i;

	i = -1;
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
	free(*line);
	next_line(0, line);
	free(*line);
	next_line(0, line);
	if (**line != 'l')
		display_error("Bad player 2");
	else
		info->p2 = ft_strcdup(strrchr(*line, '/') + 1, '.');
}

void		check_map(t_affi *affi, t_parse *info, char **line)
{
	(void)affi;
	next_line(0, line);
	info->map_height = ft_atoi(*line + 8);
	info->map_width = ft_atoi(*line + 9 + ft_intlen(info->map_height));
	free(*line);
	return ;
}
