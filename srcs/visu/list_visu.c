/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:54:13 by rbalbous          #+#    #+#             */
/*   Updated: 2018/05/05 22:23:24 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void		skip(char **line)
{
	int		i;
	int		pi_height;

	i = 0;
	pi_height = ft_atoi(*line + 6);
	free(*line);
	while (i < pi_height)
	{
		new_line(line, 2);
		i++;
	}
	next_line(0, line);
}

int			check_link(t_parse *info, char **line)
{
	(void)info;
	while (ft_strncmp("Piece", *line, 5) == 0)
	{
		skip(line);
		if (ft_strncmp(*line, "<got (X)", 8) != 0)
		{
			info->last_player = 1;
			new_line(line, 1);
			if (ft_strncmp("Piece", *line, 5) != 0)
				break ;
		}
		else if (ft_strncmp(*line, "<got (O)", 8) != 0)
		{
			info->last_player = 2;
			new_line(line, 1);
			if (ft_strncmp("Piece", *line, 5) != 0)
				break ;
		}
	}
	return (1);
}

int			parse_off(t_parse *info)
{
	char *line;

	next_line(0, &line);
	if (!check_link(info, &line))
		return (0);
	if (ft_strncmp("Plateau", line, 7) != 0)
	{
		free(line);
		info->parse_finished = 1;
		return (0);
	}
	free(line);
	return (1);
}

t_turn		*next_turn(t_turn *current, t_parse *info)
{
	t_turn		*new;
	char		*line;
	int			i;

	i = -1;
	new_line(&line, 2);
	if (!(new = malloc(sizeof(t_turn) * 1)))
		display_error("malloc error");
	new->turn_nb_p1 = current->turn_nb_p1 + (info->last_player == 1);
	new->turn_nb_p2 = current->turn_nb_p2 + (info->last_player == 2);
	new->next = NULL;
	new->prev = current;
	current->next = new;
	if (!(new->map = malloc(sizeof(char*) * (info->map_height + 1))))
		display_error("malloc error");
	while (++i < info->map_height)
		next_line(0, &new->map[i]);
	new->map[i] = 0;
	current = new;
	return (current);
}
