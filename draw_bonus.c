float rayDirX0 = g_cub.player.dirX - g_cub.player.planeX;
float rayDirY0 = g_cub.player.dirY - g_cub.player.planeY;
float rayDirX1 = g_cub.player.dirX + g_cub.player.planeX;
float rayDirY1 = g_cub.player.dirY + g_cub.player.planeY;
int p = y - window->height / 2;
float posZ = 0.5 * window->height;
float rowDistance = posZ / p;
float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / window->width;
float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / window->width;
float floorX = g_cub.player.posX + rowDistance * rayDirX0;
float floorY = g_cub.player.posY + rowDistance * rayDirY0;
for(int x = 0; x < window->width; ++x)
{
	int cellX = (int)(floorX);
	int cellY = (int)(floorY);
	int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
	int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
	floorX += floorStepX;
	floorY += floorStepY;
	int checkerBoardPattern = (int)(cellX + cellY) & 1;
	int floorTexture;
	if(checkerBoardPattern == 0) floorTexture = 3;
	else floorTexture = 4;
	int ceilingTexture = 6;
	int color;
	color = g_cub.texture[floorTexture][texWidth * ty + tx];
	color = (color >> 1) & 8355711;
	window->buf[y][x] = color;
	color = g_cub.texture[ceilingTexture][texWidth * ty + tx];
	window->buf[window->height - y - 1][x] = color;
}