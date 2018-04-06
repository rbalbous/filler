/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 16:54:13 by rbalbous          #+#    #+#             */
/*   Updated: 2018/04/06 14:50:46 by rbalbous         ###   ########.fr       */
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

int			check_link2(t_parse *info, char *line, t_turn *new)
{
	if (ft_strncmp("==", line, 2) == 0)
	{
		free(line);
		if (new->turn_nb_p2 > new->turn_nb_p1)
			new->turn_nb_p2++;
		else
			new->turn_nb_p1++;
		info->parse_finished = 1;
		return (0);
	}
	free(line);
	return (1);
}

int			check_link(t_parse *info, char *line, t_turn *new)
{
	next_line(0, &line);
	while (ft_strncmp("Piece", line, 5) == 0)
	{
		skip(&line);
		if (ft_strncmp(line, "<got (O)", 8) == 0 &&
		ft_strcmp(line, "<got (O): [0, 0]") != 0)
		{
			new->turn_nb_p1++;
			new_line(&line, 1);
			break ;
		}
		if (ft_strncmp(line, "<got (X)", 8) == 0 &&
		ft_strcmp(line, "<got (X): [0, 0]") != 0)
		{
			new->turn_nb_p2++;
			new_line(&line, 1);
			break ;
		}
		new_line(&line, 1);
	}
	new_line(&line, 1);
	return (check_link2(info, line, new));
}

t_turn		*next_turn(t_turn *current, t_parse *info)
{
	t_turn		*new;
	char		*line;
	int			i;

	i = -1;
	if (!(new = malloc(sizeof(t_turn) * 1)))
		display_error("malloc error");
	new->turn_nb_p1 = current->turn_nb_p1;
	new->turn_nb_p2 = current->turn_nb_p2;
	if (!check_link(info, line, new))
		return (NULL);
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
