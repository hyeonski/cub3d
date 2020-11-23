typedef struct	s_tile
{
	void	*imgptr;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
}				t_tile;

typedef struct  s_player
{
    int			x;
	int			y;
	int			width;
	int			height;
	int			color;

	void		*imgptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_player;

typedef struct	s_game
{
	void		*mlx;
	void		*win;
	t_tile		tile;
	t_player	player;

	int			map[ROWS][COLS];
}				t_game;