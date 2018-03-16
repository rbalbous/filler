/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:51 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/16 17:09:05 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include <SDL.h>
# include "ft_printf.h"

# define BACKGROUND_DAY 0x00FFFFFF
# define BACKGROUND_NIGHT 0x00000000
# define P1_DAY 0xE60F00
# define P1_NIGHT 0x9300AF
# define P2_DAY 0x00FFE5
# define P2_NIGHT 0x40FF00
# define P1_LST_DAY 0xFF584D
# define P1_LST_NIGHT 0xD91AFF
# define P2_LST_DAY 0x99FFF5
# define P2_LST_NIGHT 0x8CFF66

typedef	struct	s_map
{
	char	**map;
	int		height;
	int		width;
	int		x;
	int		y;
	char	player;
	char	opponent;
	int		over;
}				t_map;

typedef struct	s_piece
{
	char	**piece;
	int		height;
	int		width;
	int		x;
	int		y;
	int		x_result;
	int		y_result;
}				t_piece;

typedef	struct	s_turn	t_turn;
typedef struct	s_rect	t_rect;
typedef struct	s_point	t_point;
typedef struct	s_parse	t_parse;
typedef	union	u_color	t_color;
typedef	struct	s_affi	t_affi;

struct	s_parse
{
	char	*p1;
	char	*p2;
	int		map_height;
	int		map_width;
	int		parse_finished;
};

struct s_point
{
	int		x;
	int		y;
};

struct	s_turn
{
	char	**map;
	t_turn	*next;
	t_turn	*prev;
};

struct	s_rect
{
	int		x;
	int		y;
	int		length;
	int		width;
};

struct	s_affi
{
	SDL_Window	*win;
	SDL_Event	event;
	SDL_Surface	*surface;
	int			pixel;
	int			win_height;
	int			win_width;
	t_point		start_x;
	t_point		start_o;
	t_turn		*current;
	Uint8		pause : 1;
	Uint8		grid;
};

union				u_color
{
	int				color;
	unsigned char	rgb[4];
};

int				create_map(t_map *map, char *line);
int				create_piece(t_piece *pi, char *line);
void			free_map(t_map *map);
void			get_piece(char **piece, t_map *info);
void			free_piece(t_piece *pi);
void			get_map(t_map *map, char *line);
void			filler_break(t_map *map, t_piece *pi);
int				algo_filler(t_map *map, t_piece *pi);
int				place_piece(t_map *map, t_piece *pi);
int				min_dist(t_map *map, t_piece *pi);
int				check_distance(t_map *map, t_piece *pi);


t_parse			parser_visu(t_affi *affi, t_turn **current);
t_turn			*next_turn(t_turn *current, t_parse *info);
void			check_map(t_affi *affi, t_parse *info, char **line);
void			check_players_header(t_parse *info, char **line);
void			display_error(char *str);
char			*ft_strcdup(const char *src, int c);
void			next_line(int fd, char **line);

#endif
