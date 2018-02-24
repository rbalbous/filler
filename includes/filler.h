/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:51 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/24 16:51:30 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include "ft_printf.h"
# include <fcntl.h>
# define IWAN 0

typedef	struct	s_map
{
	int		height;
	int		width;
	int		p_height;
	int		p_width;
	int		x;
	int		y;
	int		x_result;
	int		y_result;
	char	player;
	char	opponent;
}				t_map;

char	**create_map(char **map, char *line, t_map *info);
char	**create_piece(char **piece, char *line, t_map *info);
void	get_piece(char **piece, t_map *info);
char	**get_map(char **map, char *line, t_map *info);
void	filler_break(char **map, char **piece, t_map *info);
int		algo_filler(char **piece, char **map, t_map *info);
int		place_piece(char **map, char **piece, t_map *info);

#endif
