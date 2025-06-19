#include "fuel_bar.h"
#include "structs_b.h"


static void	set_gauge_color(t_gauge_color *color, double ratio)
{
	if (ratio < 0.25)
	{
		color->r = 15;
		color->g = 20;
		color->b = 80 + (int)(380 * ratio);
	}
	else if (ratio < 0.5)
	{
		color->r = 15;
		color->g = 20 + (int)(240 * (ratio - 0.25));
		color->b = 175;
	}
	else if (ratio < 0.75)
	{
		color->r = 15 + (int)(100 * (ratio - 0.5));
		color->g = 80 + (int)(400 * (ratio - 0.5));
		color->b = 175;
	}
	else
	{
		color->r = 40 + (int)(240 * (ratio - 0.75));
		color->g = 180;
		color->b = 175 - (int)(120 * (ratio - 0.75));
	}
	color->color = (color->r << 16) | (color->g << 8) | color->b;
}

static void	draw_gauge_segment(t_image_cub *img, int y, t_gauge_color color)
{
	int	x;

	x = GAUGE_X;
	while (x < GAUGE_X + GAUGE_WIDTH)
	{
		hud_set_pixel(img, x, y, color.color);
		x++;
	}
}

static void	draw_gauge_border(t_image_cub *img)
{
	static int	border_color = 0x00305070;
	int			x;
	int			y;

	y = GAUGE_Y - GAUGE_BORDER;
	while (y < GAUGE_Y + GAUGE_HEIGHT + GAUGE_BORDER)
	{
		x = GAUGE_X - GAUGE_BORDER;
		while (x < GAUGE_X + GAUGE_WIDTH + GAUGE_BORDER)
		{
			if (x < GAUGE_X || x >= GAUGE_X + GAUGE_WIDTH || \
				y < GAUGE_Y || y >= GAUGE_Y + GAUGE_HEIGHT)
				hud_set_pixel(img, x, y, border_color);
			x++;
		}
		y++;
	}
}

static void	draw_gauge_background(t_image_cub *img)
{
	static int	bg_color = 0x00101825;
	int			x;
	int			y;

	y = GAUGE_Y;
	while (y < GAUGE_Y + GAUGE_HEIGHT)
	{
		x = GAUGE_X;
		while (x < GAUGE_X + GAUGE_WIDTH)
		{
			hud_set_pixel(img, x, y, bg_color);
			x++;
		}
		y++;
	}
}

void	draw_fuel_gauge(t_image_cub *img, int fuel_level)
{
	int				y;
	int				fuel_height;
	double			gradient_ratio;
	t_gauge_color	color;

	if (fuel_level < 0)
		fuel_level = 0;
	if (fuel_level > 100)
		fuel_level = 100;
	fuel_height = (GAUGE_HEIGHT * fuel_level) / 100;
	draw_gauge_border(img);
	draw_gauge_background(img);
	y = GAUGE_Y + GAUGE_HEIGHT - 1;
	while (y >= GAUGE_Y + GAUGE_HEIGHT - fuel_height)
	{
		gradient_ratio = (double)(y - (GAUGE_Y + GAUGE_HEIGHT - fuel_height))
			/ (double)fuel_height;
		gradient_ratio = 1.0 - gradient_ratio;
		set_gauge_color(&color, gradient_ratio);
		draw_gauge_segment(img, y, color);
		y--;
	}
}
