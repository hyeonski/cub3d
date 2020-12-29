/*
** MY_STRUCT_H : 헤더에 추가할 구조체 작성.
** -Start- 줄과 -End- 줄 사이에 사용할 구조체 들을 작성해주세요!
** 여러 구조체를 사용한다면 줄바꿈 후 계속 작성하면 됩니다!
*/

/* -Start-Write your structs just right down */

typedef struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct		s_window
{
	int				width;
	int				height;
	int				**buf;
}					t_window;

typedef struct		s_texture
{
	int				width;
	int				height;
	int				*data;
}					t_texture;

typedef struct		s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef struct		s_map
{
	int				width;
	int				height;
	char			**data;
}					t_map;

typedef struct		s_control
{
	int				keyboard[127];
}					t_control;

typedef struct		s_str_arr
{
	int				size;
	char			**elem;
}					t_str_arr;

typedef struct		s_ray
{
	double			raydir_x;
	double			raydir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
}					t_ray;

typedef struct		s_draw_info
{
	t_ray			ray;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_draw_info;

typedef struct		s_tex_info
{
	int				tex_num;
	int				tex_width;
	int				tex_height;
	double			wall_x;
	int				tex_x;
	double			step;
	double			tex_pos;
}					t_tex_info;

typedef struct		s_sprite_info{
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
}					t_sprite_info;

typedef struct		s_sprite
{
	double			x;
	double			y;
	int				tex_num;
}					t_sprite;

typedef struct		s_cub
{
	void			*mlx;
	void			*win;
	void			*imgptr;
	int				*data;
	t_window		window;
	t_player		player;
	t_texture		texture[5];
	t_rgb			floor;
	t_rgb			ceiling;
	t_list			*sprite;
	t_map			map;
	t_control		control;
	double			*z_buffer;
}					t_cub;

extern t_cub		g_cub;

/* -End- finish!# */
