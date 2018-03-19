/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:51 by rbalbous          #+#    #+#             */
/*   Updated: 2018/03/19 18:48:58 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include "ft_printf.h"

# define BACKGROUND_DAY 0x000000
# define BACKGROUND_NIGHT 0x000000
# define P1_DAY 0xE60F00
# define P1_NIGHT 0x9300AF
# define P2_DAY 0x1A1AFF
# define P2_NIGHT 0x00CC00
# define P1_LST_DAY 0xffCCCC
# define P1_LST_NIGHT 0xD91AFF
# define P2_LST_DAY 0x99FFF5
# define P2_LST_NIGHT 0x99FF99

# define R 0xb30000
# define B 0x000099
# define C 0x9999ff
# define P 0xff9999
# define G 0x78877e


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
	int		turn_nb;
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
	TTF_Font	*font;
	SDL_Surface *message;
	SDL_Surface *message2;
	int			pixel;
	int			win_height;
	int			win_width;
	t_point		start_x;
	t_point		start_o;
	t_turn		*current;
	Uint8		pause : 1;
	Uint8		grid;
	int			last_event;
	double		k;
	int			font_size;
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


t_parse			parser_visu(t_affi *disp, t_turn **current);
t_turn			*next_turn(t_turn *current, t_parse *info);
void			check_map(t_affi *disp, t_parse *info, char **line);
void			check_players_header(t_parse *info, char **line);
void			display_error(char *str);
char			*ft_strcdup(const char *src, int c);
void			next_line(int fd, char **line);
void			draw_next(t_affi *disp, t_parse *info);
void			draw_last(t_affi *disp, t_parse *info);
void			put_rect(t_rect rect, Uint32 color, t_affi *disp);
void			put_line(t_affi *disp, t_point start, t_point end, Uint32 color);
int				ft_abs(int x);
void			put_line(t_affi *disp, t_point start, t_point end, Uint32 color);
void			put_pixel(int x, int y, Uint32 color, t_affi *disp);
Uint32			get_color(t_color c1, t_color c2, double k);

#endif
