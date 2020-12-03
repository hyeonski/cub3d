typedef struct	s_map
{
	int		map[MAPX][MAPY];
	int		grid_color;
	int		wall_color;

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
	int			width;
	int			height;

	t_player	player;
	t_map		map;
}				t_game;