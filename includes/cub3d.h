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

// typedef struct	s_img
// {
// 	void	*img;
// 	int		*data;

// 	int		size_l;
// 	int		bpp;
// 	int		endian;
// 	int		img_width;
// 	int		img_height;
// }				t_img;

// typedef struct	s_pair_int
// {
// 	int x;
// 	int y;
// }				t_pair_int;

// typedef struct	s_pair_double
// {
// 	double x;
// 	double y;
// }				t_pair_double;

// typedef struct	s_point_of_view
// {
// 	int horizontal;
// 	int vertical;
// }				t_point_of_view;



typedef struct	s_temp
{
	float rayDirX0;
	float rayDirY0;
	float rayDirX1;
	float rayDirY1;
	int p;
	float posZ;
	float rowDistance;
	float floorStepX;
	float floorStepY;
	float floorX;
	float floorY;
	int cellX;
	int cellY;
	int tx;
	int ty;
	int floorTexture;
	int ceilingTexture;
	int color;
	double cameraX;
	
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int texNum;
	double wallX;
	int texX;
	double step;
	double texPos;
	int texY;
	double floorXWall;
	double floorYWall;
	double distWall;
	double distPlayer;
	double currentDist;
	double weight;
	double currentFloorX;
	double currentFloorY;
	int floorTexX;
	int	floorTexY;
	int checkerBoardPattern;
	double oldDirX;
	double oldPlaneX;
}				t_temp;

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
	// t_point_of_view	movement;
	// t_point_of_view	rotation;

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
	// t_pair_int	old_mouse_point;
	// t_pair_int	new_mouse_point;
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
	t_temp		temp;
	double		*zBuffer;
}				t_cub;

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