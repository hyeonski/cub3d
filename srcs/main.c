/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:47 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/13 17:46:36 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define numSprites 19

t_cub	g_cub;

/*struct	Sprite
{
	double		x;
	double		y;
	int			texture;
};

struct Sprite	sprite[numSprites] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

// typedef struct	s_info
// {
// 	double posX;
// 	double posY;
// 	double dirX;
// 	double dirY;
// 	double planeX;
// 	double planeY;
// 	void	*mlx;
// 	void	*win;
// 	int		key_a;
// 	int		key_w;
// 	int		key_s;
// 	int		key_d;
// 	int		key_esc;
// 	t_img	img;
// 	int		buf[height][width];
// 	double	zBuffer[width];
// 	int		**texture;
// 	double	moveSpeed;
// 	double	rotSpeed;
// }				t_info;

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;
*/

void	key_update(void);

// static int	compare(const void *first, const void *second)
// {
// 	if (*(int *)first > *(int *)second)
// 		return (1);
// 	else if (*(int *)first < *(int *)second)
// 		return (-1);
// 	else
// 		return (0);
// }

// void	sort_order(t_pair *orders, int amount)
// {
// 	t_pair	tmp;

// 	for (int i = 0; i < amount; i++)
// 	{
// 		for (int j = 0; j < amount - 1; j++)
// 		{
// 			if (orders[j].first > orders[j + 1].first)
// 			{
// 				tmp.first = orders[j].first;
// 				tmp.second = orders[j].second;
// 				orders[j].first = orders[j + 1].first;
// 				orders[j].second = orders[j + 1].second;
// 				orders[j + 1].first = tmp.first;
// 				orders[j + 1].second = tmp.second;
// 			}
// 		}
// 	}
// }

// void	sortSprites(int *order, double *dist, int amount)
// {
// 	t_pair	*sprites;

// 	//std::vector<std::pair<double, int>> sprites(amount);
// 	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
// 	for (int i = 0; i < amount; i++)
// 	{
// 		sprites[i].first = dist[i];
// 		sprites[i].second = order[i];
// 	}
// 	sort_order(sprites, amount);
// 	//std::sort(sprites.begin(), sprites.end());
// 	for (int i = 0; i < amount; i++)
// 	{
// 		dist[i] = sprites[amount - i - 1].first;
// 		order[i] = sprites[amount - i - 1].second;
// 	}
// 	free(sprites);
// }

void	draw(void)
{
	for (int y = 0; y < g_cub.window.height; y++)
	{
		for (int x = 0; x < g_cub.window.width; x++)
		{
			g_cub.data[y * g_cub.window.width + x] = g_cub.window.buf[y][x];
		}
	}
	mlx_put_image_to_window(g_cub.mlx, g_cub.win, g_cub.imgptr, 0, 0);
}

void	calc(void)
{
	//FLOOR CASTING
	for(int y = g_cub.window.height / 2 + 1; y < g_cub.window.height; ++y)
	{
		// // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		// float rayDirX0 = g_cub.player.dirX - g_cub.player.planeX;
		// float rayDirY0 = g_cub.player.dirY - g_cub.player.planeY;
		// float rayDirX1 = g_cub.player.dirX + g_cub.player.planeX;
		// float rayDirY1 = g_cub.player.dirY + g_cub.player.planeY;
		// // Current y position compared to the center of the screen (the horizon)
		// int p = y - g_cub.window.height / 2;
		// // Vertical position of the camera.
		// float posZ = 0.5 * g_cub.window.height;
		// // Horizontal distance from the camera to the floor for the current row.
		// // 0.5 is the z position exactly in the middle between floor and ceiling.
		// float rowDistance = posZ / p;
		// // calculate the real world step vector we have to add for each x (parallel to camera plane)
		// // adding step by step avoids multiplications with a weight in the inner loop
		// float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / g_cub.window.width;
		// float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / g_cub.window.width;
		// // real world coordinates of the leftmost column. This will be updated as we step to the right.
		// float floorX = g_cub.player.posX + rowDistance * rayDirX0;
		// float floorY = g_cub.player.posY + rowDistance * rayDirY0;
		// for(int x = 0; x < g_cub.window.width; ++x)
		// {
		// 	// the cell coord is simply got from the integer parts of floorX and floorY
		// 	int cellX = (int)(floorX);
		// 	int cellY = (int)(floorY);
		// 	// get the texture coordinate from the fractional part
		// 	int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
		// 	int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
		// 	floorX += floorStepX;
		// 	floorY += floorStepY;
		// 	// choose texture and draw the pixel
		// 	int checkerBoardPattern = (int)(cellX + cellY) & 1;
		// 	int floorTexture;
		// 	if(checkerBoardPattern == 0) floorTexture = 3;
		// 	else floorTexture = 4;
		// 	int ceilingTexture = 6;
		// 	int color;
		// 	// floor
		// 	color = g_cub.texture[floorTexture][texWidth * ty + tx];
		// 	color = (color >> 1) & 8355711; // make a bit darker
		// 	g_cub.window.buf[y][x] = color;
		// 	//ceiling (symmetrical, at height - y - 1 instead of y)
		// 	color = g_cub.texture[ceilingTexture][texWidth * ty + tx];
		// 	color = (color >> 1) & 8355711; // make a bit darker
		// 	g_cub.window.buf[g_cub.window.height - y - 1][x] = color;
		// }
		for(int x = 0; x < g_cub.window.width; ++x)
		{
			int color;
			
			//floor
			color = (g_cub.floor.r << 16) + (g_cub.floor.g << 8) + g_cub.floor.b;
			g_cub.window.buf[y][x] = color;
			//ceiling (symmetrical, at height - y - 1 instead of y)
			color = (g_cub.ceiling.r << 16) + (g_cub.ceiling.g << 8) + g_cub.ceiling.b;
			g_cub.window.buf[g_cub.window.height - y - 1][x] = color;
		}
	}
	// WALL CASTING
	for(int x = 0; x < g_cub.window.width; x++)
	{
		//calculate ray position and direction
		double cameraX = 2 * x / (double)g_cub.window.width - 1; //x-coordinate in camera space
		g_cub.ray.rayDirX = g_cub.player.dirX + g_cub.player.planeX * cameraX;
		g_cub.ray.rayDirY = g_cub.player.dirY + g_cub.player.planeY * cameraX;
		//which box of the map we're in
		g_cub.ray.mapX = (int)g_cub.player.posX;
		g_cub.ray.mapY = (int)g_cub.player.posY;
		//length of ray from one x or y-side to next x or y-side
		g_cub.ray.deltaDistX = fabs(1 / g_cub.ray.rayDirX);
		g_cub.ray.deltaDistY = fabs(1 / g_cub.ray.rayDirY);
		//what direction to step in x or y-direction (either +1 or -1)
		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (g_cub.ray.rayDirX < 0)
		{
			g_cub.ray.stepX = -1;
			g_cub.ray.sideDistX = (g_cub.player.posX - g_cub.ray.mapX) * g_cub.ray.deltaDistX;
		}
		else
		{
			g_cub.ray.stepX = 1;
			g_cub.ray.sideDistX = (g_cub.ray.mapX + 1.0 - g_cub.player.posX) * g_cub.ray.deltaDistX;
		}
		if (g_cub.ray.rayDirY < 0)
		{
			g_cub.ray.stepY = -1;
			g_cub.ray.sideDistY = (g_cub.player.posY - g_cub.ray.mapY) * g_cub.ray.deltaDistY;
		}
		else
		{
			g_cub.ray.stepY = 1;
			g_cub.ray.sideDistY = (g_cub.ray.mapY + 1.0 - g_cub.player.posY) * g_cub.ray.deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (g_cub.ray.sideDistX < g_cub.ray.sideDistY)
			{
				g_cub.ray.sideDistX += g_cub.ray.deltaDistX;
				g_cub.ray.mapX +=g_cub.ray. stepX;
				side = 0;
			}
			else
			{
				g_cub.ray.sideDistY += g_cub.ray.deltaDistY;
				g_cub.ray.mapY += g_cub.ray.stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (g_cub.map.data[g_cub.ray.mapX][g_cub.ray.mapY] == '1')
				hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
		if (side == 0)
			g_cub.ray.perpWallDist = (g_cub.ray.mapX - g_cub.player.posX + (1 - g_cub.ray.stepX) / 2) / g_cub.ray.rayDirX;
		else
			g_cub.ray.perpWallDist = (g_cub.ray.mapY - g_cub.player.posY + (1 - g_cub.ray.stepY) / 2) / g_cub.ray.rayDirY;
		//Calculate height of line to draw on screen
		int lineHeight = (int)(g_cub.window.height / g_cub.ray.perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + g_cub.window.height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + g_cub.window.height / 2;
		if (drawEnd >= g_cub.window.height)
			drawEnd = g_cub.window.height - 1;
		//texturing calculations
		int texNum;
		if (side == 1)
		{
			texNum = g_cub.ray.rayDirY > 0 ? 0 : 1;
		}
		else
		{
			texNum = g_cub.ray.rayDirX > 0 ? 2 : 3;
		}
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = g_cub.player.posY + g_cub.ray.perpWallDist * g_cub.ray.rayDirY;
		else
			wallX = g_cub.player.posX + g_cub.ray.perpWallDist * g_cub.ray.rayDirX;
		wallX -= floor((wallX));
		//x coordinate on the texture
		int texX = (int)(wallX * (double)g_cub.texture[texNum].width);
		if (side == 0 && g_cub.ray.rayDirX > 0)
			texX = g_cub.texture[texNum].width - texX - 1;
		if (side == 1 && g_cub.ray.rayDirY < 0)
			texX = g_cub.texture[texNum].width - texX - 1;
		// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * g_cub.texture[texNum].height / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - g_cub.window.height / 2 + lineHeight / 2) * step;
		for (int y = drawStart; y < drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (g_cub.texture[texNum].height - 1);
			texPos += step;
			int color = g_cub.texture[texNum].data[g_cub.texture[texNum].height * texY + texX];
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (side == 1)
				color = (color >> 1) & 8355711;
			g_cub.window.buf[y][x] = color;
		}

		//SET THE ZBUFFER FOR THE SPRITE CASTING
		g_cub.zBuffer[x] = g_cub.ray.perpWallDist; //perpendicular distance is used
	}

	// //SPRITE CASTING
	// //sort sprites from far to close
	// for(int i = 0; i < numSprites; i++)
	// {
	// 	spriteOrder[i] = i;
	// 	spriteDistance[i] = ((g_cub.posX - sprite[i].x) * (g_cub.posX - sprite[i].x) + (g_cub.posY - sprite[i].y) * (g_cub.posY - sprite[i].y)); //sqrt not taken, unneeded
	// }
	// sortSprites(spriteOrder, spriteDistance, numSprites);
	// //after sorting the sprites, do the projection and draw them
	// for(int i = 0; i < numSprites; i++)
	// {
	// 	//translate sprite position to relative to camera
	// 	double spriteX = sprite[spriteOrder[i]].x - g_cub.posX;
	// 	double spriteY = sprite[spriteOrder[i]].y - g_cub.posY;

	// 	//transform sprite with the inverse camera matrix
	// 	// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
	// 	// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
	// 	// [ planeY   dirY ]                                          [ -planeY  planeX ]

	// 	double invDet = 1.0 / (g_cub.planeX * g_cub.dirY - g_cub.player.dirX * g_cub.planeY); //required for correct matrix multiplication

	// 	double transformX = invDet * (g_cub.dirY * spriteX - g_cub.dirX * spriteY);
	// 	double transformY = invDet * (-g_cub.planeY * spriteX + g_cub.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

	// 	int spriteScreenX = (int)((width / 2) * (1 + transformX / transformY));

	// 	//parameters for scaling and moving the sprites
	// 	#define uDiv 1
	// 	#define vDiv 1
	// 	#define vMove 0.0
	// 	int vMoveScreen = (int)(vMove / transformY);

	// 	//calculate height of the sprite on screen
	// 	int spriteHeight = (int)fabs((height / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
	// 	//calculate lowest and highest pixel to fill in current stripe
	// 	int drawStartY = -spriteHeight / 2 + height / 2 + vMoveScreen;
	// 	if(drawStartY < 0) drawStartY = 0;
	// 	int drawEndY = spriteHeight / 2 + height / 2 + vMoveScreen;
	// 	if(drawEndY >= height) drawEndY = height - 1;

	// 	//calculate width of the sprite
	// 	int spriteWidth = (int)fabs((height / transformY) / uDiv);
	// 	int drawStartX = -spriteWidth / 2 + spriteScreenX;
	// 	if(drawStartX < 0) drawStartX = 0;
	// 	int drawEndX = spriteWidth / 2 + spriteScreenX;
	// 	if(drawEndX >= width) drawEndX = width - 1;

	// 	//loop through every vertical stripe of the sprite on screen
	// 	for(int stripe = drawStartX; stripe < drawEndX; stripe++)
	// 	{
	// 		int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256);
	// 		//the conditions in the if are:
	// 		//1) it's in front of camera plane so you don't see things behind you
	// 		//2) it's on the screen (left)
	// 		//3) it's on the screen (right)
	// 		//4) ZBuffer, with perpendicular distance
	// 		if(transformY > 0 && stripe > 0 && stripe < width && transformY < g_cub.zBuffer[stripe])
	// 		for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
	// 		{
	// 			int d = (y-vMoveScreen) * 256 - height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
	// 			int texY = ((d * texHeight) / spriteHeight) / 256;
	// 			int color = g_cub.texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
	// 			if((color & 0x00FFFFFF) != 0) g_cub.window.buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
	// 		}
	// 	}
	// }
}

int	main_loop(void)
{
	calc();
	draw();
	update_player_rotation();
	return (0);
}

void	update_player_rotation(void)
{
	if (g_cub.control.keyboard[KEY_W])
	{
		if (g_cub.map.data[(int)(g_cub.player.posX + g_cub.player.dirX * g_cub.player.moveSpeed)][(int)(g_cub.player.posY)] == '0')
			g_cub.player.posX += g_cub.player.dirX * g_cub.player.moveSpeed;
		if (g_cub.map.data[(int)(g_cub.player.posX)][(int)(g_cub.player.posY + g_cub.player.dirY * g_cub.player.moveSpeed)] == '0')
			g_cub.player.posY += g_cub.player.dirY * g_cub.player.moveSpeed;
	}
	//move backwards if no wall behind you
	if (g_cub.control.keyboard[KEY_S])
	{
		if (g_cub.map.data[(int)(g_cub.player.posX - g_cub.player.dirX * g_cub.player.moveSpeed)][(int)(g_cub.player.posY)] == '0')
			g_cub.player.posX -= g_cub.player.dirX * g_cub.player.moveSpeed;
		if (g_cub.map.data[(int)(g_cub.player.posX)][(int)(g_cub.player.posY - g_cub.player.dirY * g_cub.player.moveSpeed)] == '0')
			g_cub.player.posY -= g_cub.player.dirY * g_cub.player.moveSpeed;
	}
	//rotate to the right
	if (g_cub.control.keyboard[KEY_D])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = g_cub.player.dirX;
		g_cub.player.dirX = g_cub.player.dirX * cos(-g_cub.player.rotSpeed) - g_cub.player.dirY * sin(-g_cub.player.rotSpeed);
		g_cub.player.dirY = oldDirX * sin(-g_cub.player.rotSpeed) + g_cub.player.dirY * cos(-g_cub.player.rotSpeed);
		double oldPlaneX = g_cub.player.planeX;
		g_cub.player.planeX = g_cub.player.planeX * cos(-g_cub.player.rotSpeed) - g_cub.player.planeY * sin(-g_cub.player.rotSpeed);
		g_cub.player.planeY = oldPlaneX * sin(-g_cub.player.rotSpeed) + g_cub.player.planeY * cos(-g_cub.player.rotSpeed);
	}
	//rotate to the left
	if (g_cub.control.keyboard[KEY_A])
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = g_cub.player.dirX;
		g_cub.player.dirX = g_cub.player.dirX * cos(g_cub.player.rotSpeed) - g_cub.player.dirY * sin(g_cub.player.rotSpeed);
		g_cub.player.dirY = oldDirX * sin(g_cub.player.rotSpeed) + g_cub.player.dirY * cos(g_cub.player.rotSpeed);
		double oldPlaneX = g_cub.player.planeX;
		g_cub.player.planeX = g_cub.player.planeX * cos(g_cub.player.rotSpeed) - g_cub.player.planeY * sin(g_cub.player.rotSpeed);
		g_cub.player.planeY = oldPlaneX * sin(g_cub.player.rotSpeed) + g_cub.player.planeY * cos(g_cub.player.rotSpeed);
	}
}

void		init_game(void)
{
	int		temp;

	g_cub.player.moveSpeed = 0.05;
	g_cub.player.rotSpeed = 0.02;
	
	g_cub.win = mlx_new_window(g_cub.mlx, g_cub.window.width, g_cub.window.height, "mlx");

	g_cub.imgptr = mlx_new_image(g_cub.mlx, g_cub.window.width, g_cub.window.height);
	g_cub.data = (int *)mlx_get_data_addr(g_cub.imgptr, &temp, &temp, &temp);

	mlx_loop_hook(g_cub.mlx, &main_loop, &g_cub.control);
	mlx_hook(g_cub.win, X_EVENT_KEY_PRESS, 0, &key_press, &g_cub.control);
	mlx_hook(g_cub.win, X_EVENT_KEY_RELEASE, 0, &key_release, &g_cub.control);

	mlx_loop(g_cub.mlx);
}

int		main(int ac, char **av)
{
	ac += 0;
	g_cub.mlx = mlx_init();
	// if (argc > 3 || argc == 1
	// 	|| (argc == 3 && ft_strcmp("--save", argv[2]) != 0))
	// 	return (print_error(cuberror(invalid_argument)));
	if (!set_cub(av[1]))
		return (-1);
	// if (argc == 3)
	// {
	// 	update_scene();
	// 	save_image_to_bmp_file(g_cub.window.scene, g_cub.window.width,
	// 							g_cub.window.height);
	// }
	// else
	init_game();

	return (0);
}