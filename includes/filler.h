/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:51 by rbalbous          #+#    #+#             */
/*   Updated: 2018/02/28 18:43:41 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include "ft_printf.h"
# include <fcntl.h>

typedef	struct	s_map
{
	char	**map;
	int		height;
	int		width;
	int		x;
	int		y;
	char	player;
	char	opponent;
}				t_map;

typedef struct	s_piece
{
	char	**piece;
	int		height;
	int		width;
}				t_piece;

int		create_map(t_map *map, char *line);
int		create_piece(t_piece *pi, char *line);
void	free_map(t_map *map);
void	get_piece(char **piece, t_map *info);
void	free_piece(t_piece *pi);
void	get_map(t_map *map, char *line);
void	filler_break(t_map *map, t_piece *pi);
int		algo_filler(t_map *map, t_piece *pi);
int		place_piece(t_map *map, t_piece *pi);
int		min_dist(t_map *map, int ypiece, int xpiece);
int		check_distance(t_map *map, t_piece *pi);

#endif
