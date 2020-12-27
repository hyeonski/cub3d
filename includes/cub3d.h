#include <fcntl.h>
#include <stdlib.h>
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <mlx.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include "get_next_line.h"

typedef struct	s_player
{
	double	pos_x;
	double	pos_y;
	double 	dir_x;
	double 	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
}				t_player;

typedef struct	s_window
{
	int 	width;
	int 	height;
	int		**buf;
}				t_window;

typedef struct	s_texture
{
	int			width;
	int			height;
	int			*data;
}				t_texture;

typedef struct	s_rgb
{
	int r;
	int g;
	int b;
}				t_rgb;

typedef struct	s_map
{
	int			width;
	int			height;
	char		**data;
}				t_map;

typedef struct	s_control
{
	int			keyboard[101];
}				t_control;

typedef struct	s_str_arr {
	int		size;
	char	**elem;
}				t_str_arr;

typedef struct	s_ray
{
	double raydir_x;
	double raydir_y;
	int map_x;
	int map_y;
	double side_dist_x;
	double side_dist_y;
	double delta_dist_x;
	double delta_dist_y;
	int step_x;
	int step_y;
	int	side;
}				t_ray;

typedef struct	s_draw_info
{
	t_ray	ray;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}				t_draw_info;

typedef struct	s_tex_info
{
	int		tex_num;
	int		tex_width;
	int		tex_height;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
}				t_tex_info;

typedef struct	s_sprite_info{
	int				w;
	int				h;
	double			sprite_x;
	double			sprite_y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_h;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_w;
	int				draw_start_x;
	int				draw_end_x;
	int				tex_width;
	int				tex_height;
	int				tex_x;
	int				tex_y;
	int				d;
	unsigned int	color;
}				t_sprite_info;

typedef struct	s_sprite {
	double			x;
	double			y;
	int				tex_num;
}				t_sprite;

typedef struct	s_cub
{
	void		*mlx;
	void		*win;

	void		*imgptr;
	int			*data;
	t_window	window;
	t_player	player;
	t_texture	texture[5];
	t_rgb		floor;
	t_rgb		ceiling;
	t_list		*sprite;
	t_map		map;
	t_control	control;
	double		*zBuffer;
}				t_cub;

typedef struct s_pair_int
{
	int x;
	int y;
}				t_pair_int;

extern t_cub g_cub;

int			set_cub(char *map_file_path);
int			init_cub(t_str_arr *conf);
int			read_file_to_buf(char *map_file_path, t_str_arr *conf);
int			parse_value(char *key);
t_rgb		set_rgbcolor(char *value);
void		set_window(int width, int height);
int			set_texture(char *key, char *file_path);
int			load_texture(t_texture *texture, char *file_path);
void		check_map_size(t_str_arr *arr, int i);
void		set_map(char **strs, int start);
void		init_player(t_map *map, t_player *player);
void		set_player(t_player *player, int x, int y, char dir);
void		free_2d_arr(char **arr, int size);
int			ft_2d_arr_size(char **arr);
int			is_contain(char c, char *str);
char		**init_chars_array(int row, int col, char c);
int			ft_list_strjoin(t_str_arr *str_arr, char *str);
int			print_error(char *message);
int			is_valid_file_name(char *file_path);
int			is_valid_cub(t_str_arr *conf);
int			key_press(int key, t_control *control);
int			key_release(int key, t_control *control);
void		update_player_rotation(t_player *player, t_map *map);
int			main_loop(t_cub *cub);
void		update_screen(t_cub *cub, t_window *window);