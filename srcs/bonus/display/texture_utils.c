#include "structs_b.h"
#include "image.h"

#include <stdbool.h>

/* Get pixel with bilinear filtering for smoother texture sampling */
static int	interpolate_color(int c1, int c2, double factor)
{
	int	r1;
	int	g1;
	int	b1;
	int	r2;
	int	g2;

	r1 = (c1 >> 16) & 0xFF;
	g1 = (c1 >> 8) & 0xFF;
	b1 = c1 & 0xFF;
	r2 = (c2 >> 16) & 0xFF;
	g2 = (c2 >> 8) & 0xFF;
	return (((int)(r1 + (r2 - r1) * factor) << 16) |
			((int)(g1 + (g2 - g1) * factor) << 8) |
			((int)(b1 + (c2 & (0xFF - b1)) * factor)));
}

/* Sample texture with better quality for non-integer coordinates */
int	get_texture_pixel_filtered(t_image_cub *texture, double x, double y)
{
	int		x0;
	int		y0;
	double	fx;
	double	fy;
	int		c[4];

	x0 = (int)x;
	y0 = (int)y;
	fx = x - x0;
	fy = y - y0;
	if (x0 >= texture->width - 1 || y0 >= texture->height - 1)
		return (get_color(texture, x0, y0));
	c[0] = get_color(texture, x0, y0);
	c[1] = get_color(texture, x0 + 1, y0);
	c[2] = get_color(texture, x0, y0 + 1);
	c[3] = get_color(texture, x0 + 1, y0 + 1);
	c[0] = interpolate_color(c[0], c[1], fx);
	c[2] = interpolate_color(c[2], c[3], fx);
	return (interpolate_color(c[0], c[2], fy));
}

/* Calculate optimal mipmap level based on distance */
int	calculate_mipmap_level(double distance)
{
	int	level;

	level = 0;
	distance = distance / 5.0;
	while (distance > 1.0 && level < 3)
	{
		distance /= 2.0;
		level++;
	}
	return (level);
}

/* Check if texture dimensions are power of 2 (optimal for rendering) */
bool	is_power_of_two(int n)
{
	return ((n > 0) && ((n & (n - 1)) == 0));
}

/* Get recommended texture size for optimal performance */
void	get_optimal_texture_size(int *width, int *height)
{
	if (!is_power_of_two(*width))
		*width = 1;
	if (!is_power_of_two(*height))
		*height = 1;
}
