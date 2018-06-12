/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbalbous <rbalbous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 16:01:51 by rbalbous          #+#    #+#             */
/*   Updated: 2018/05/07 16:05:21 by rbalbous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include <SDL.h>
# include <SDL_ttf.h>
# include "ft_printf.h"

# define BLACK		"\x1B[30m"
# define RED		"\x1B[31m"
# define GREEN		"\x1B[32m"
# define YELLOW		"\x1B[33m"
# define BLUE		"\x1B[34m"
# define MAGENTA	"\x1B[35m"
# define CYAN		"\x1B[36m"
# define WHITE		"\x1B[37m"
# define RESET		"\x1B[0m"

# define BACKGROUND_DAY		0x000000
# define BACKGROUND_NIGHT	0x000000
# define P1_DAY				0xE60F00
# define P1_NIGHT			0x800080
# define P2_DAY				0x1A1AFF
# define P2_NIGHT			0x00cc00
# define P1_LST_DAY			0xffCCCC
# define P1_LST_NIGHT		0xffccff
# define P2_LST_DAY			0x99FFF5
# define P2_LST_NIGHT		0x99FF99

# define R	0xb30000
# define B	0x000099
# define C	0x9999ff
# define P	0xff9999
# define G	0x78877e

typedef struct s_piece	t_piece;
typedef	struct s_map	t_map;
typedef	struct s_plyr	t_player;
typedef	struct s_turn	t_turn;
typedef struct s_dots	t_dots;
typedef struct s_rect	t_rect;
typedef struct s_point	t_point;
typedef struct s_parse	t_parse;
typedef	struct s_disp	t_disp;
typedef	union u_color	t_color;

struct			s_map
{
	char	**map;
	char	**last_map;
	t_dots	**al_map;
	t_dots	**tmp_map;
	int		height;
	int		width;
	int		x;
	int		y;
	int		nb_op;
	char	player;
	char	opponent;
	char	current;
	char	over;
};

struct			s_piece
{
	char	**piece;
	int		height;
	int		width;
	int		x;
	int		y;
	int		x_result;
	int		y_result;
};

struct			s_dots
{
	int			dist;
	int			belong;
};

struct			s_plyr
{
	int			x;
	int			y;
	char		belong;
	t_player	*next;
};

struct			s_parse
{
	char	*p1;
	char	*p2;
	int		p1_len;
	int		p2_len;
	int		map_height;
	int		map_width;
	int		parse_finished;
	int		last_player;
};

struct			s_point
{
	int		x;
	int		y;
};

struct			s_turn
{
	char	**map;
	int		turn_nb_p1;
	int		turn_nb_p2;
	t_turn	*next;
	t_turn	*prev;
};

struct			s_rect
{
	int		x;
	int		y;
	int		length;
	int		width;
};

struct			s_disp
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
	t_turn		*first;
	t_turn		*temp;
	Uint8		pause : 1;
	Uint8		grid;
	int			last_event;
	double		k;
	int			font_size;
	int			tinsel;
};

union			u_color
{
	int				color;
	unsigned char	rgb[4];
};

void			create_map(t_map *map);
void			create_piece(t_piece *pi);
void			get_piece(char **piece, t_map *info);
void			free_piece(t_piece *pi);
void			get_map(t_map *map);
void			filler_break(t_map *map, t_piece *pi);
int				algo_filler(t_map *map, t_piece *pi);
int				place_piece(t_map *map, t_piece *pi);
int				min_dist(t_map *map, t_piece *pi);
int				check_distance(t_map *map, t_piece *pi);

void			init_list(t_map *map);
int				filler_algo(t_map *map, t_piece *pi);
void			recur_bot(t_map *map, int x, int y, int dist);
void			recur_top(t_map *map, int x, int y, int dist);
void			recur_left(t_map *map, int x, int y, int dist);
void			recur_right(t_map *map, int x, int y, int dist);
void			copy_map(t_map *map);
void			update_map(t_map *map);
void			create_last_map(t_map *map);
void			first_map(t_player *first, t_map *map);
int				get_most_territory(t_map *map, t_piece *pi);
void			put_piece(t_map *map, t_piece *pi);
int				place_pi(t_map *map, t_piece *pi, int x, int y);
int				phoney_algo(t_map *map, t_piece *pi);
void			al_cpy(t_map *map);

t_parse			parser_visu(t_disp *disp, t_turn **current);
t_turn			*next_turn(t_turn *current, t_parse *info);
void			check_map(t_disp *disp, t_parse *info, char **line);
void			check_players_header(t_parse *info, char **line, int i);
void			display_error(char *str);
char			*ft_strcdup(const char *src, int c);
void			next_line(int fd, char **line);
void			draw_next(t_disp *disp, t_parse *info);
void			draw_last(t_disp *disp, t_parse *info);
void			put_rect(t_rect rect, Uint32 color, t_disp *disp);
void			put_line(t_disp *disp, t_point start, t_point end
, Uint32 color);
void			put_pixel(int x, int y, Uint32 color, t_disp *disp);
Uint32			get_color(t_color c1, t_color c2, double k);
void			new_line(char	**line, int i);
void			get_event(t_disp *disp, t_parse *info, t_turn *first);
void			put_score(t_disp *disp, t_parse *info);
void			put_colors(t_disp *disp, int x, int y);
void			clean_quit(t_disp *disp);
SDL_Color		color_conv(unsigned int hexvalue);
void			disp_tinsel(t_disp *disp, t_parse *info);
int				check_link(t_parse *info, char **line);
int				parse_off(t_parse *info);

#endif
