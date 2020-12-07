typedef struct	s_map
{
	int		map[MAPX][MAPY];

	void	*imgptr;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
}				t_map;

typedef struct  s_player
{
    double		px;
	double		py;
	double		pdx;
	double		pdy;
	double		pa;

	int			width;
	int			height;
	int			color;
}				t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	
	t_player	player;
	t_map		map;

	int			width;
	int			height;
	int			map_color;
	int			grid_color;
	int			wall_color;
	int			row_count;
	int			column_count;
}				t_game;