#include "fuel_bar.h"
#include "image_b.h"
#include "structs_b.h"

void	hud_set_pixel(t_image_cub *img, int x, int y, int color)
{
	int	offset;

	if (x < 0 || y < 0 || x >= HUD_WIDTH || y >= HUD_HEIGHT)
		return ;
	offset = (y * img->line_bytes) + (x * (img->pixel_bits / 8));
	if (img->endian == 0)
	{
		*(img->buffer + offset) = (color) & 0xFF;
		*(img->buffer + offset + 1) = (color >> 8) & 0xFF;
		*(img->buffer + offset + 2) = (color >> 16) & 0xFF;
		*(img->buffer + offset + 3) = (color >> 24) & 0xFF;
	}
	else
	{
		*(img->buffer + offset) = (color >> 24) & 0xFF;
		*(img->buffer + offset + 1) = (color >> 16) & 0xFF;
		*(img->buffer + offset + 2) = (color >> 8) & 0xFF;
		*(img->buffer + offset + 3) = (color) & 0xFF;
	}
}

static void	draw_lantern_outline(t_image_cub *img)
{
	static int	outline_color = 0x00FFFFFF;
	static int	x = GAUGE_X - 2;
	static int	y = GAUGE_Y - 2;

	while (x < GAUGE_X + GAUGE_WIDTH + 2)
	{
		hud_set_pixel(img, x, y, outline_color);
		x++;
	}
	y = GAUGE_Y + GAUGE_HEIGHT + 1;
	x = GAUGE_X - 2;
	while (x < GAUGE_X + GAUGE_WIDTH + 2)
	{
		hud_set_pixel(img, x, y, outline_color);
		x++;
	}
	x = GAUGE_X - 2;
	y = GAUGE_Y - 2;
	while (y <= GAUGE_Y + GAUGE_HEIGHT + 1)
	{
		hud_set_pixel(img, x, y, outline_color);
		hud_set_pixel(img, GAUGE_X + GAUGE_WIDTH + 1, y, outline_color);
		y++;
	}
}

static void	fill_hud_background(t_image_cub *img)
{
	int	x;
	int	y;
	int	color;

	color = 0x00152035;
	y = 0;
	while (y < HUD_HEIGHT)
	{
		x = 0;
		while (x < HUD_WIDTH)
		{
			hud_set_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

bool	display_minifuel(t_main_struct *main_struct)
{
	int	i;
	int	j;

	i = 0;
	while (i < HUD_HEIGHT)
	{
		j = 0;
		while (j < HUD_WIDTH)
		{
			change_pixel_color(main_struct->frame, \
				get_color(main_struct->fuel_bar, j, i), HUD_X + j, HUD_Y + i);
			j = j + 4;
		}
		i++;
	}
	return (true);
}

bool	display_hud(t_main_struct *main_struct)
{
	static int	last_fuel_level = -1;

	if (!main_struct->fuel_bar)
		return (false);
	if (last_fuel_level != (main_struct->fuel * 100))
	{
		fill_hud_background(main_struct->fuel_bar);
		draw_lantern_outline(main_struct->fuel_bar);
		draw_fuel_gauge(main_struct->fuel_bar,
			((main_struct->fuel - 0.05) * 105));
		last_fuel_level = (main_struct->fuel * 100);
	}
	display_minifuel(main_struct);
	return (true);
}
