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
	void            *mlx;
	void            *win;
	t_player        player;
    t_background    background;
	t_map			map;

	int		width;
	int		height;

	int		row_count;
	int		column_count;
	int		grid_color;
}				t_window;