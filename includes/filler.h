/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:51 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/10 21:14:41 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include "ft_printf.h"
# define IWAN 0

typedef	struct	s_map
{
	int		height;
	int		width;
	int		p_height;
	int		p_width;
	int		xp_top;
	int		yp_top;
	int		xp_bot;
	int		yp_bot;
	int		p_rheight;
	int		p_rwidth;
	int		x;
	int		y;
	char	player;
	char	opponent;
}				t_map;

char	**create_map(char **map, char *line, t_map *info);
char	**create_piece(char **piece, char *line, t_map *info);
void	get_piece(char **piece, t_map *info);
char	**get_map(char **map, char *line, t_map *info);
void	fi_break(char **map, char **piece, t_map *info);
int		algo_filler(char **piece, char **map, t_map *info);
int		fi_place_piece(char **map, char **piece, t_map *info);

#endif
