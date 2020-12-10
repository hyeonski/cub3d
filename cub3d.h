#include <fcntl.h>
#include <stdlib.h>
#include "key_macos.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <mlx.h>
#include <unistd.h>
#include <limits.h>
#include "get_next_line/get_next_line.h"

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

typedef struct	s_player
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	// t_point_of_view	movement;
	// t_point_of_view	rotation;

}				t_player;

typedef struct	s_window
{
	int width;
	int height;
	int **scene;
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

// typedef struct	s_cub
// {
// 	void	*mlx;
// 	void	*win;
// 	t_img	img;
// 	int		buf[1][1];
// 	double	moveSpeed;
// 	double	rotSpeed;

// 	t_window	window;
// 	t_player	player;
// 	t_texture	texture[5];
// 	t_rgb		floor;
// 	t_rgb		ceil;
// 	// t_list		*sprite;
// 	t_map		map;
// 	t_control	control;
// 	double		*zbuf;
// }				t_cub;

typedef struct	s_str_arr {
	int		size;
	char	**elem;
}				t_str_arr;

#define texWidth 64
#define texHeight 64
#define mapWidth 6
#define mapHeight 6
#define width 640
#define height 480

typedef struct	s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

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
	double rayDirX;
	double rayDirY;
	int mapX;
	int mapY;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	int stepX;
	int stepY;
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

typedef struct	s_info
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	void	*mlx;
	void	*win;
	t_img	img;
	t_temp	temp;
	int		buf[height][width];
	int		**texture;
	double	moveSpeed;
	double	rotSpeed;
}				t_info;

// extern t_cub g_cub;

int		map_parser(char *map, t_str_arr *str_arr);
int		is_included(char c, char *set);
void	free_2d_arr(char **arr, int size);
