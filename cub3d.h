typedef struct  s_player
{
    int			x;
	int			y;
	int			color;

	void		*imgptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_player;

typedef struct	s_background
{
	int			width;
	int			height;
	int			color;

	void		*imgptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_background;

typedef struct	s_map
{
	int			map[ROWS][COLS];
	int			width;
	int			height;
	int			color;
	int			block_size;

	void		*imgptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_map;

typedef struct	s_window
{
	int		width;
	int		height;
}				t_window;

typedef struct 	s_game
{
	void	*mlx;
	void	*win;

	t_player        player;
    t_background    background;
	t_map			map;
	t_window		window;
}				t_game;