/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lodev.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 19:53:20 by yohlee            #+#    #+#             */
/*   Updated: 2020/12/10 13:21:27 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	worldMap[mapWidth][mapHeight] =
{
	{1,1,1,1,1,1},
	{1,0,0,0,0,1},
	{1,0,1,0,0,1},
	{1,0,0,0,0,1},
	{1,0,0,0,0,1},
	{1,1,1,1,1,1}
};

void	draw(t_info *info)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			info->img.data[y * width + x] = info->buf[y][x];
		}
	}
	mlx_put_image_to_window(info->mlx, info->win, info->img.img, 0, 0);
}

void	calc(t_info *info)
{
	//FLOOR CASTING
	for(int y = 0; y < height; y++)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		info->temp.rayDirX0 = info->dirX - info->planeX;
		info->temp.rayDirY0 = info->dirY - info->planeY;
		info->temp.rayDirX1 = info->dirX + info->planeX;
		info->temp.rayDirY1 = info->dirY + info->planeY;

		// Current y position compared to the center of the screen (the horizon)
		info->temp.p = y - height / 2;

		// Vertical position of the camera.
		info->temp.posZ = 0.5 * height;

		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = info->temp.posZ / info->temp.p;

		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (info->temp.rayDirX1 - info->temp.rayDirX0) / width;
		float floorStepY = rowDistance * (info->temp.rayDirY1 - info->temp.rayDirY0) / width;

		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = info->posX + rowDistance * info->temp.rayDirX0;
		float floorY = info->posY + rowDistance * info->temp.rayDirY0;

		for(int x = 0; x < width; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			info->temp. cellX = (int)(floorX);
			info->temp. cellY = (int)(floorY);

			// get the texture coordinate from the fractional part
			info->temp. tx = (int)(texWidth * (floorX - info->temp.cellX)) & (texWidth - 1);
			info->temp.ty = (int)(texHeight * (floorY - info->temp.cellY)) & (texHeight - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			// choose texture and draw the pixel
			info->temp.floorTexture = 3;
			info->temp.ceilingTexture = 6;

			// floor
			info->temp.color = info->texture[info->temp.floorTexture][texWidth * info->temp.ty + info->temp.tx];
			info->temp.color = (info->temp.color >> 1) & 8355711; // make a bit darker

			info->buf[y][x] = info->temp.color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			info->temp.color = info->texture[info->temp.ceilingTexture][texWidth * info->temp.ty + info->temp.tx];
			info->temp.color = (info->temp.color >> 1) & 8355711; // make a bit darker

			info->buf[height - y - 1][x] = info->temp.color;
		}
	}
	//WALL CASTING
	for(int x = 0; x < width; x++)
	{
		info->temp.cameraX = 2 * x / (double)width - 1;
		info->temp.rayDirX = info->dirX + info->planeX * info->temp.cameraX;
		info->temp.rayDirY = info->dirY + info->planeY * info->temp.cameraX;
		
		info->temp.mapX = (int)info->posX;
		info->temp.mapY = (int)info->posY;

		//length of ray from current position to next x or y-side
		
		//length of ray from one x or y-side to next x or y-side
		info->temp.deltaDistX = fabs(1 / info->temp.rayDirX);
		info->temp.deltaDistY = fabs(1 / info->temp.rayDirY);
		
		//what direction to step in x or y-direction (either +1 or -1)
		
		info->temp.hit = 0; //was there a wall hit?

		if (info->temp.rayDirX < 0)
		{
			info->temp.stepX = -1;
			info->temp.sideDistX = (info->posX - info->temp.mapX) * info->temp.deltaDistX;
		}
		else
		{
			info->temp.stepX = 1;
			info->temp.sideDistX = (info->temp.mapX + 1.0 - info->posX) * info->temp.deltaDistX;
		}
		if (info->temp.rayDirY < 0)
		{
			info->temp.stepY = -1;
			info->temp.sideDistY = (info->posY - info->temp.mapY) * info->temp.deltaDistY;
		}
		else
		{
			info->temp.stepY = 1;
			info->temp.sideDistY = (info->temp.mapY + 1.0 - info->posY) * info->temp.deltaDistY;
		}

		while (info->temp.hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (info->temp.sideDistX < info->temp.sideDistY)
			{
				info->temp.sideDistX += info->temp.deltaDistX;
				info->temp.mapX += info->temp.stepX;
				info->temp.side = 0;
			}
			else
			{
				info->temp.sideDistY += info->temp.deltaDistY;
				info->temp.mapY += info->temp.stepY;
				info->temp.side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[info->temp.mapX][info->temp.mapY] > 0)
				info->temp.hit = 1;
		}
		if (info->temp.side == 0)
			info->temp.perpWallDist = (info->temp.mapX - info->posX + (1 - info->temp.stepX) / 2) / info->temp.rayDirX;
		else
			info->temp.perpWallDist = (info->temp.mapY - info->posY + (1 - info->temp.stepY) / 2) / info->temp.rayDirY;

		//Calculate height of line to draw on screen
		info->temp.lineHeight = (int)(height / info->temp.perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		info->temp.drawStart = -info->temp.lineHeight / 2 + height / 2;
		if (info->temp.drawStart < 0)
			info->temp.drawStart = 0;
		info->temp.drawEnd = info->temp.lineHeight / 2 + height / 2;
		if (info->temp.drawEnd >= height)
			info->temp.drawEnd = height - 1;

		// texturing calculations
		info->temp.texNum = worldMap[info->temp.mapX][info->temp.mapY] - 1;

		// calculate value of wallX
		if (info->temp.side == 0)
			info->temp.wallX = info->posY + info->temp.perpWallDist * info->temp.rayDirY;
		else
			info->temp.wallX = info->posX + info->temp.perpWallDist * info->temp.rayDirX;
		info->temp.wallX -= floor(info->temp.wallX);

		// x coordinate on the texture
		info->temp.texX = (int)(info->temp.wallX * (double)texWidth);
		if (info->temp.side == 0 && info->temp.rayDirX > 0)
			info->temp.texX = texWidth - info->temp.texX - 1;
		if (info->temp.side == 1 && info->temp.rayDirY < 0)
			info->temp.texX = texWidth - info->temp.texX - 1;

		// How much to increase the texture coordinate perscreen pixel
		info->temp.step = 1.0 * texHeight / info->temp.lineHeight;

		// Starting texture coordinate
		info->temp.texPos = (info->temp.drawStart - height / 2 + info->temp.lineHeight / 2) * info->temp.step;

		for (int y = info->temp.drawStart; y < info->temp.drawEnd; y++)
		{
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			info->temp.texY = (int)info->temp.texPos & (texHeight - 1);
			info->temp.texPos += info->temp.step;

			info->temp.color = info->texture[info->temp.texNum][texHeight * info->temp.texY + info->temp.texX];

			// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if (info->temp.side == 1)
				info->temp.color = (info->temp.color >> 1) & 8355711;

			info->buf[y][x] = info->temp.color;
		}

		//FLOOR CASTING (vertical version, directly after drawing the vertical wall stripe for the current x)

		//4 different wall directions possible
		if (info->temp.side == 0 && info->temp.rayDirX > 0)
		{
			info->temp.floorXWall = info->temp.mapX;
			info->temp.floorYWall = info->temp.mapY + info->temp.wallX;
		}
		else if(info->temp.side == 0 && info->temp.rayDirX < 0)
		{
			info->temp.floorXWall = info->temp.mapX + 1.0;
			info->temp.floorYWall = info->temp.mapY + info->temp.wallX;
		}
		else if(info->temp.side == 1 && info->temp.rayDirY > 0)
		{
			info->temp.floorXWall =info->temp. mapX + info->temp.wallX;
			info->temp.floorYWall =info->temp. mapY;
		}
		else
		{
			info->temp.floorXWall =info->temp. mapX + info->temp.wallX;
			info->temp.floorYWall = info->temp.mapY + 1.0;
		}


		info->temp.distWall = info->temp.perpWallDist;
		info->temp.distPlayer = 0.0;

		if (info->temp.drawEnd < 0)
			info->temp.drawEnd = height; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for (int y = info->temp.drawEnd + 1; y < height; y++)
		{
			info->temp.currentDist = height / (2.0 * y - height); //you could make a small lookup table for this instead

			info->temp.weight = (info->temp.currentDist - info->temp.distPlayer) / (info->temp.distWall - info->temp.distPlayer);

			info->temp.currentFloorX = info->temp.weight * info->temp.floorXWall + (1.0 - info->temp.weight) * info->posX;
			info->temp.currentFloorY = info->temp.weight * info->temp.floorYWall + (1.0 - info->temp.weight) * info->posY;

			info->temp.floorTexX = (int)(info->temp.currentFloorX * texWidth) % texWidth;
			info->temp.floorTexY = (int)(info->temp.currentFloorY * texHeight) % texHeight;

			info->temp.checkerBoardPattern = ((int)(info->temp.currentFloorX) + (int)(info->temp.currentFloorY)) % 2;
			if	(info->temp.checkerBoardPattern == 0)
				info->temp.floorTexture = 3;
			else
				info->temp.floorTexture = 4;

			//floor
			info->buf[y][x] = (info->texture[info->temp.floorTexture][texWidth * info->temp.floorTexY + info->temp.floorTexX] >> 1) & 8355711;
			//ceiling (symmetrical!)
			info->buf[height - y][x] = info->texture[6][texWidth * info->temp.floorTexY + info->temp.floorTexX];
		}
	}
}

int	main_loop(t_info *info)
{
	calc(info);
	draw(info);
	return (0);
}

int	key_press(int key, t_info *info)
{
	if (key == KEY_W)
	{
		if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX += info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
			info->posY += info->dirY * info->moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == KEY_S)
	{
		if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
			info->posX -= info->dirX * info->moveSpeed;
		if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
			info->posY -= info->dirY * info->moveSpeed;
	}
	//rotate to the right
	if (key == KEY_D)
	{
		//both camera direction and camera plane must be rotated
		info->temp.oldDirX = info->dirX;
		info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
		info->dirY = info->temp.oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
		info->temp.oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
		info->planeY = info->temp.oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
	}
	//rotate to the left
	if (key == KEY_A)
	{
		//both camera direction and camera plane must be rotated
		info->temp.oldDirX = info->dirX;
		info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
		info->dirY = info->temp.oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
		info->temp.oldPlaneX = info->planeX;
		info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
		info->planeY = info->temp.oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
	}
	if (key == KEY_ESC)
		exit(0);
	printf("x: %f , y: %f\n", info->posX, info->posY);
	return (0);
}

void	load_image(t_info *info, int *texture, char *path, t_img *img)
{
	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->size_l, &img->endian);
	for (int y = 0; y < img->img_height; y++)
	{
		for (int x = 0; x < img->img_width; x++)
		{
			texture[img->img_width * y + x] = img->data[img->img_width * y + x];
		}
	}
	mlx_destroy_image(info->mlx, img->img);
}

void	load_texture(t_info *info)
{
	t_img	img;

	load_image(info, info->texture[0], "textures/eagle.xpm", &img);
	load_image(info, info->texture[1], "textures/redbrick.xpm", &img);
	load_image(info, info->texture[2], "textures/purplestone.xpm", &img);
	load_image(info, info->texture[3], "textures/greystone.xpm", &img);
	load_image(info, info->texture[4], "textures/bluestone.xpm", &img);
	load_image(info, info->texture[5], "textures/mossy.xpm", &img);
	load_image(info, info->texture[6], "textures/wood.xpm", &img);
	load_image(info, info->texture[7], "textures/colorstone.xpm", &img);
}


int	main(int ac, char **av)
{
	t_info		info;
	t_str_arr	str_arr;

	info.mlx = mlx_init();
	info.posX = 1.1;
	info.posY = 1.1;
	info.dirX = -1.0;
	info.dirY = 0.0;
	info.planeX = 0.0;
	info.planeY = 0.66;

	// map_parser(av[1], &str_arr);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			info.buf[i][j] = 0;
		}
	}

	if (!(info.texture = (int **)malloc(sizeof(int *) * 8)))
		return (-1);
	for (int i = 0; i < 8; i++)
	{
		if (!(info.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
			return (-1);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < texHeight * texWidth; j++)
		{
			info.texture[i][j] = 0;
		}
	}

	load_texture(&info);

	info.moveSpeed = 0.05;
	info.rotSpeed = 0.05;
	
	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

	mlx_loop(info.mlx);
}