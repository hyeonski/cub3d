/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 18:18:08 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/30 10:06:07 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <string.h>
# include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include "get_next_line.h"
# include "key_macos.h"

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
/*
** Src is : ../srcs/arr_utils.c
*/
int					ft_2d_arr_size(char **arr);
void				free_2d_arr(char **arr, int size);
char				**init_chars_array(int row, int col, char c);

/*
** Src is : ../srcs/set_cub.c
*/
int					read_file_to_buf(char *map_file_path, t_str_arr *conf);
int					init_sprite(t_list **begin_list, t_map *map);
int					init_cub(t_str_arr *conf);
int					set_cub(char *map_file_path);

/*
** Src is : ../srcs/valid_key.c
*/
int					check_key(char *key, int *check_list);
int					is_valid_rgb(char *rgb);
int					check_rfc(char **token, int size);
int					is_valid_key(char *key, int *check_list);

/*
** Src is : ../srcs/validation.c
*/
int					is_valid_file_name(char *file_path);
int					is_check_list_completed(int *check_list);
int					is_valid_cub(t_str_arr *conf);

/*
** Src is : ../srcs/dda.c
*/
void				init_ray(int x, int w, t_ray *ray, t_player *player);
void				calc_delta_dist(t_ray *ray);
void				calc_step_side_dist(t_ray *ray, t_player *player);
void				dda(t_ray *ray);
void				calc_perp_wall_dist(t_draw_info *draw_info,
		t_ray *ray, t_player *player);

/*
** Src is : ../srcs/set_map.c
*/
void				set_map(char **strs, int start);
void				check_map_size(t_str_arr *arr, int i);

/*
** Src is : ../srcs/player_move.c
*/
void				move_player_front_back(char **map,
		t_player *player, double move_speed);
void				move_player_left_right(char **map,
		t_player *player, double move_speed);
void				rotate_player(t_player *player,
		double rotate_speed);
void				update_player_rotation(t_player *player, t_map *map);

/*
** Src is : ../srcs/valid_map.c
*/
int					is_contain_only_map_arg(char **map, int width, int height);
int					dfs(char ***map, int i, int j);
int					is_valid_map_structure(char **map, int width, int height);
int					is_valid_map(t_str_arr *conf,
		int *i, int *check_list, t_map *map);

/*
** Src is : ../srcs/draw_sprite.c
*/
void				calc_draw_sprite_info(t_sprite_info *info,
								t_sprite *sprite);
void				calc_draw_sprite_info_sub(t_sprite_info *info);
void				draw_ele(t_sprite *sprite);
void				draw_ele_sub(t_sprite_info *info,
								t_sprite *sprite, int stripe);
void				draw_sprite(t_cub *cub);

/*
** Src is : ../srcs/utils.c
*/
int					ft_list_strjoin(t_str_arr *str_arr, char *str);
int					is_contain(char c, char *str);
int					is_num_str(const char *str);
int					count_chars(const char *s, int c);
void				update_img_from_buf(t_window *window, int *data);

/*
** Src is : ../srcs/error.c
*/
int					print_error(char *message);

/*
** Src is : ../srcs/set_player.c
*/
void				set_player(t_player *player, int x, int y, char dir);
void				init_player(t_map *map, t_player *player);

/*
** Src is : ../srcs/bmp.c
*/
void				set_int_in_char(unsigned char *start, int value);
void				write_bmp_header(int fd, int width, int height);
void				write_data(int fd, int **buf, int width, int height);
int					save_image_to_bmp_file(int **buf, int width, int height);

/*
** Src is : ../srcs/valid_map_utils.c
*/
int					is_map_arg(int c);
int					get_next_dir_x(int x, int dir);
int					get_next_dir_y(int y, int dir);

/*
** Src is : ../srcs/draw_wall.c
*/
void				get_draw_info(int x, t_draw_info *draw_info,
								t_window *window);
void				select_texture(t_tex_info *tex_info,
								t_player *player, t_draw_info *draw_info);
void				get_tex_info(t_tex_info *tex_info, t_draw_info *draw_info,
								t_ray *ray);
int					get_tex_pixel(t_tex_info *tex_info, t_draw_info *draw_info);
void				draw_wall(t_cub *cub, t_window *window);

/*
** Src is : ../srcs/key_handle.c
*/
int					key_press(int key, t_control *control);
int					key_release(int key, t_control *control);

/*
** Src is : ../srcs/draw_floor_ceil.c
*/
void				draw_floor_ceil(t_window *window,
		t_rgb *floor, t_rgb *ceiling);

/*
** Src is : ../srcs/parse_value.c
*/
int					load_texture(t_texture *texture, char *file_path);
int					set_texture(char *key, char *file_path);
void				set_window(int width, int height);
t_rgb				set_rgbcolor(char *value);
int					parse_value(char *key);

/*
** Src is : ../srcs/draw_sprite_utils.c
*/
int					compare_sprite_dist(t_sprite *lhs, t_sprite *rhs);

/*
** Src is : ../srcs/texture_utils.c
*/
void				free_texture(t_texture *texture);
void				copy_img_data(int *dest, int *src, int width, int height);

#endif
