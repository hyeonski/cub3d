/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 13:15:11 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 19:16:33 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <math.h>

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"
# include "mlx.h"
# include "key.h"

# define TEX_N 0
# define TEX_S 1
# define TEX_W 2
# define TEX_E 3
# define TEX_O 4
# define RMAX_W 1024
# define RMAX_H 768
# define RMIN_W 480
# define RMIN_H 320

typedef	struct		s_pos
{
	double			x;
	double			y;
}					t_pos;

typedef	struct		s_tex
{
	char			*path[5];
	void			*img[5];
	void			*data[5];
	int				wh[5][2];
	int				bpp;
	int				size_line;
	int				endian;
}					t_tex;

typedef struct		s_config
{
	int				res_w;
	int				res_h;
	int				grid_w;
	int				grid_h;
	int				color_f;
	int				color_c;
	t_tex			*tex;
}					t_config;

typedef	struct		s_player
{
	t_pos			*pos;
	t_pos			*dir;
	t_pos			*plane;
	double			mov_speed;
	int				rot_speed;
	int				mov_dir;
	int				rot_dir;
}					t_player;

typedef	struct		s_ray
{
	t_pos			*dir;
	double			dist;
	int				wall_h;
	int				wall_type;
	int				is_side;
	int				draw_start;
	int				draw_end;
	int				now;
}					t_ray;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
	struct s_sprite	*next;
}					t_sprite;

typedef struct		s_calwall
{
	double			wall_x;
	int				tex_x;
	int				tex_y;
}					t_calwall;

typedef struct		s_calsp
{
	int				sp_h;
	int				sp_w;
	double			inv_det;
	double			trans_x;
	double			trans_y;
	int				sp_screen_x;
	int				drawstart_y;
	int				drawend_y;
	int				drawstart_x;
	int				drawend_x;
	int				tex_x;
	int				tex_y;
	int				tex_w;
}					t_calsp;

typedef	struct		s_cub3d
{
	t_config		*conf;
	t_player		*player;
	t_ray			*ray;
	t_sprite		*sp;
	double			*zbuff;
	char			**grid;
	void			*mlx;
	void			*win;
	void			*img;
	void			*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_cub3d;

int					init_cub3d(t_cub3d *cub);
int					set_cub3d(char *map_file, t_cub3d *cub3d);
int					ck_grid_form(char *form);
int					ck_color_form(char *form);
int					ck_resolution_form(char *form);
int					check_grid(t_cub3d *cub3d);
int					free_all(t_cub3d *cub3d, int ret);
char				**join_grid(char **grid, char *line, t_cub3d *cub3d);
int					get_config(char *line, t_cub3d *cub3d);
int					is_nsew(char c);
double				deg2rad(double deg);
int					run_mlx(t_cub3d *cub3d);
int					is_wall(int new_x, int new_y, t_cub3d *cub3d);
int					raycasting(t_cub3d *cub3d);
void				render(t_cub3d *cub3d);
int					err_free(int erno, char *msg, t_cub3d *cub3d, int ret);
void				set_pos(t_pos *pos, double x, double y);
void				rotate_pos(t_pos *pos, double rad);
int					move_player(t_cub3d *cub3d);
int					rotate_player(t_cub3d *cub3d);
int					load_texture(t_cub3d *cub3d);
int					set_screen(t_cub3d *cub3d);
void				wall_on_screen();
void				ceiling_on_screen();
void				floor_on_screen();
void				sprite_on_screen();
void				sp_add_back(t_sprite **begin, int x, int y);
void				sp_update_by_dist(t_sprite **begin, t_pos *p_pos);
void				sp_clear(t_sprite **begin);
int					screen_shot(t_cub3d *cub3d);
int					calc_side_dist(t_pos *side,
						t_pos *delta, int map[], int step[]);
int					err_msg(int erno, char *msg, int ret);

#endif
